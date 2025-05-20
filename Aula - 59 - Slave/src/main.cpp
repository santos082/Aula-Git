#include <Arduino.h>         // Inclui a biblioteca principal do Arduino
#include <BluetoothSerial.h> // Inclui a biblioteca para comunicação Bluetooth Serial (usada com ESP32)
#define pinLed 2
// Cria um objeto chamado BT para gerenciar a comunicação Bluetooth
BluetoothSerial BT;

void setup()
{
  Serial.begin(9600); // Inicia a comunicação Serial com o computador a 9600 bps (bits por segundo)
  pinMode(pinLed, OUTPUT);

  // Inicia o Bluetooth com o nome "EspGuiSlave"
  if (BT.begin("EspGuiSlave"))
  {
    Serial.println("Bluetooth Iniciado com sucesso"); // Exibe mensagem de sucesso na serial
  }
  else
  {
    Serial.println("Erro ao iniciar o Bluetooth"); // Exibe mensagem de erro na serial, se não iniciar corretamente
  }
}

void loop()
{
  static bool pisca = false;
  static bool estadoLed = false;
  static int velocidade = 200;

  // Verifica se há dados disponíveis na porta Serial (enviados pelo computador, por exemplo)
  if (Serial.available())
  {
    // Lê a mensagem enviada até encontrar uma quebra de linha (\n)
    String mensagemEnviar = Serial.readStringUntil('\n');

    mensagemEnviar.trim();      // Remove espaços em branco, quebras de linha e outros caracteres extras
    BT.println(mensagemEnviar); // Envia a mensagem lida via Bluetooth
  }

  // Verifica se há dados recebidos via Bluetooth
  if (BT.available())
  {
    // Lê a mensagem recebida até encontrar uma quebra de linha (\n)
    String mensagemRecebida = BT.readStringUntil('\n');

    mensagemRecebida.trim();                                  // Remove espaços e quebras de linha extras
    Serial.println("Mensagem Recebida: " + mensagemRecebida); // Exibe a mensagem recebida na Serial

    // Verifica se a mensagem recebida foi "liga"
    if (mensagemRecebida.equals("liga"))
    {
      estadoLed = true; // Aqui você pode colocar código para ligar algum componente (ex: acender um LED)
      pisca = false;
    }

    // Verifica se a mensagem recebida foi "desliga"
    else if (mensagemRecebida.equals("desliga"))
    {
      estadoLed = false;
      pisca = false;
    }
    else if (mensagemRecebida.equals("pisca"))
    {
      pisca = true;
    }

    else if (mensagemRecebida.equals("mais rapido "))
    {
      pisca = true;
      velocidade -= 100;
      if (velocidade < 50)
      {
        velocidade = 50;
      }
    }

    else if (mensagemRecebida.equals("mais devagar"))
    {
      pisca = true;
      velocidade += 100;
      if (velocidade > 1000)
      {
        velocidade = 1000;
      }
    }

    else if (mensagemRecebida.startsWith("velocidade = "))
    {
      int tamanho = mensagemRecebida.length();
      String extracao = mensagemRecebida.substring(13, tamanho);
      int valorVel = extracao.toInt();

      if (valorVel >= 0 && valorVel <= 100)
      {
        velocidade = map(valorVel, 0, 100, 1000, 50);
      }
      else
      {
        Serial.println("valores aceitos somente entre 0 e 100");
      }
    }
  }
  if (pisca == true)
  {
    unsigned long tempoAtual = millis();
    static unsigned long tempoInicial = 0;

    if (tempoAtual - tempoInicial >= velocidade)
    {
      estadoLed = !estadoLed;
      tempoInicial = tempoAtual;
    }
  }

  digitalWrite(pinLed, estadoLed);
}
