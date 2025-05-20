/*
NOME: Guilherme
DATA: 12/05/2025
*/

#include <Arduino.h>
#include <ezTime.h>
#include "internet.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include <DHT.h>
#include "Led.h"

//* ----------- PROTOTIPAGEM ----------

void callback(char *, byte *, unsigned int);
void conectmqtt(void);

//* ------- CRIACAO DE OBJETOS
Timezone tempo;
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(5, DHT22);
Bounce Boot = Bounce();
JsonDocument doc;

Led LedESP(2);
Led ledVermelho(4);
Led ledAmarelo(19);
Led ledBranco(22);

//* ---------------------------------------------
//*     VARIAVEIS
//* ---------------------------------------------
const char *mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char *mqtt_client_id = "senai134_esp_gui";
const char *mqtt_topic_sub = "senai134/mesa03/espGui/subs";
const char *mqtt_topic_pub = "senai134/mesa03/espGui/esppub";
// Frequências default
int freqEsp = 3;
int freqVermelho = 3;
int freqAmarelo = 3;
int freqBranco = 3;

// Tempo de piscamento do LED, em milissegundos

//* ---------------------------------------------
//*     INICIO DAS ACOES
//* ---------------------------------------------
void setup()
{

  Serial.begin(9600);
  pinMode(2, OUTPUT);
  Boot.attach(0, INPUT_PULLUP);

  dht.begin();

  Serial.println(dht.readHumidity());
  Serial.println(dht.readTemperature());

  conecxaoWiFi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  LedESP.update();
  ledVermelho.update();
  ledAmarelo.update();
  ledBranco.update();

  Boot.update();
  checkWiFi();

  bool atualizacao = false;
  bool estadoBotao = false;

  if (!client.connected())
  {
    conectmqtt();
  }

  client.loop();

  static unsigned long tempoAnterior = 0;
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior > 2000)
  {
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();

    // Verificação simples de faixas válidas
    if (temperatura < 0 || temperatura > 80 || umidade < 0 || umidade > 100)
    {
      Serial.println("Leitura fora do intervalo esperado!");
      return;
    }

    doc["temperatura"] = temperatura;
    doc["umidade"] = umidade;
    doc["timestamp"] = millis();

    // Criar string para armazenar o JSON
    String mensagem;
    serializeJson(doc, mensagem); // Agora escreve direto na String

    // Publica os dados
    client.publish(mqtt_topic_pub, mensagem.c_str()); // .c_str() converte String para const char*
    Serial.print("Publicado: ");
    Serial.println(mensagem);

    tempoAnterior = tempoAtual;
  }

  if (Boot.changed())
  {
    estadoBotao = !Boot.read(); // Atualiza o estado do botão

    // Cria o objeto JSON para enviar o estado do botão
    doc["estadoBotao"] = estadoBotao;

    // Serializando o JSON para string
    String mensagemBotao;
    serializeJson(doc, mensagemBotao);

    // Publicando o JSON no tópico MQTT
    client.publish(mqtt_topic_pub, mensagemBotao.c_str());
    Serial.print("Publicado: ");
    Serial.println(mensagemBotao);
  }
}

//* ------- CALLBACK DO MQTT - MENSAGEM RECEBIDA -----------

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensagem recebida em ");
  Serial.print(topic);
  Serial.print(": ");

  // Montar a string da mensagem recebida
  String mensagem = "";
  for (int i = 0; i < length; i++)
  {
    mensagem += (char)payload[i];
  }
  Serial.println(mensagem);

  // Parse do JSON
  JsonDocument doc;
  DeserializationError erro = deserializeJson(doc, mensagem);

  if (erro)
  {
    Serial.printf("Erro %s no formato");
  }
  else
  {
    if (!doc["estadoLed"].isNull())
    {
      int acaoLed = doc["estadoLed"];

      switch (acaoLed)
      {
      case 0:
        LedESP.desligar();
        ledAmarelo.desligar();
        ledBranco.desligar();
        ledVermelho.desligar();
        break;

      case 1:
        LedESP.ligar();
        ledAmarelo.ligar();
        ledBranco.ligar();
        ledVermelho.ligar();
        break;

      case 2:

        // Se vier um objeto com frequencias, atualiza os valores
        if (!doc["frequenciaLed"].isNull())
        {
          JsonObject freq = doc["frequenciaLed"];

          if (freq["esp"])
            freqEsp = freq["esp"];
          if (freq["vermelho"])
            freqVermelho = freq["vermelho"];
          if (freq["amarelo"])
            freqAmarelo = freq["amarelo"];
          if (freq["branco"])
            freqBranco = freq["branco"];
        }

        LedESP.piscar(freqEsp);
        ledVermelho.piscar(freqVermelho);
        ledAmarelo.piscar(freqAmarelo);
        ledBranco.piscar(freqBranco);
        break;

      default:
        Serial.println("Opcao nao implementada");
        break;
      }
    }
  }
}

//* ------- CONECTAR AO MQTT -----

void conectmqtt()
{
  while (!client.connected())
  {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(mqtt_client_id))
    {
      Serial.println("Conectado");
      client.subscribe(mqtt_topic_sub);
    }
    else
    {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s");
      delay(5000);
    }
  }
}