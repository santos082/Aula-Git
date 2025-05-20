#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

// ********************** DEFINICOES *********************

const char enderecoSlave[] = {};
#define num_botoes 7

#define pinBotaoA 13
#define pinBotaoB 12
#define pinBotaoC 14
#define pinBotaoD 27
#define pinBotaoE 26
#define pinBotaoF 25
#define pinBotaoK 33
#define pinAnalogicoX 35
#define pinAnalogicoY 34

const char pinJoyStick[num_botoes] = {

    pinBotaoA,
    pinBotaoB,
    pinBotaoC,
    pinBotaoD,
    pinBotaoE,
    pinBotaoF,
    pinBotaoK

};

// TODO fazer os analogicos X e Y

// *********************   OBJETOS   *********************

BluetoothSerial BT;
Bounce *joystick = new Bounce[num_botoes];
JsonDocument doc;
LiquidCrystal_I2C lcd(0x27, 20, 4);

// *********************  VARIAVEIS  *********************

// **************** PROTOTIPO DAS FUNCOES ************
void reconectarBT();
void IniciarBT();

enum pinsBotoes // serve para dar nome, enumerar, dar nome de numeros...
{
  botaoA = 0,
  botaoB = 1,
  botaoC = 2,
  botaoD = 3,
  botaoE = 4,
  botaoF = 5,
  botaoK = 6,

};

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("oiiii");

  void IniciarBT();
  for (char i = 0; i < num_botoes; i++)
  {
    joystick[i].attach(pinJoyStick[i], INPUT);
  }
}

void loop()
{
  bool atualizacao = false;
  int mudancaBotoes[num_botoes] = {0, 0, 0, 0, 0, 0, 0};
  int estadoBotoes[num_botoes] = {0, 0, 0, 0, 0, 0, 0};

  static int analogicoAnterior[2] = {9, 9};
  int analogicoAtual[2] = {analogRead(pinAnalogicoX) / 200, analogRead(pinAnalogicoY) / 200};

  doc.clear();

  for (char j = 0; j < num_botoes; j++)
  {
    joystick[j].update();

    if (joystick[j].changed())
      ; // verifica a alteracao no botao, se ele foi apertado ou se ele foi solto
    {
      char chave[10];
      sprintf(chave, "botao%d", j);
      doc[chave] = !joystick[j].read();
      mudancaBotoes[j] = 1;
      estadoBotoes[j] = !joystick[j].read();
      atualizacao = true;
    }
  }

  if (analogicoAtual[0] != analogicoAnterior[0])
  {
    doc["anX"] = analogicoAtual[0];
    atualizacao = true;
  }

  if (analogicoAtual[1] != analogicoAnterior[1])
  {
    doc["anY"] = analogicoAtual[1];
    atualizacao = true;
  }

  analogicoAnterior[0] = analogicoAtual[0];
  analogicoAnterior[1] = analogicoAtual[1];

  String payload; // carga ultil, é o conteúdo da mensagem que você quer realmente enviar ou receber

  if (atualizacao)
  {
    serializeJson(doc, payload);
    Serial.println(payload);
  }

  if (BT.connected())
  {
    BT.println(payload);
  }
  else
  {
    reconectarBT();
  }
  if (atualizacao)
  {
    for (int i = 0; i < num_botoes; i++)
    {
      if (mudancaBotoes[i])
      {
        lcd.setCursor(0, 0);
        lcd.printf("Botao %d esta %s", i, estadoBotoes ? "Precionado" : "Solto");
      }
    }
  }
}

void reconectarBT()
{
  if (BT.connected())
  {
    return;
  }
  Serial.println("Tentando reconectar...");
  BT.end();
  delay(1000);
  IniciarBT();
}

void IniciarBT()
{
  Serial.println("Esp32 Iniciado"); // Envia a mensagem "Esp32 Iniciado" para o monitor serial, para indicar que o ESP32 foi iniciado.

  bool iniciouSucesso = BT.begin("MASTER-GUI", true); // Tenta inicializar o Bluetooth com o nome "MASTER-GUI" e com a função de começar como master (true). O resultado da tentativa é armazenado na variável booleana 'iniciouSucesso'.

  if (iniciouSucesso) // Verifica se a inicialização do Bluetooth foi bem-sucedida.
  {
    Serial.print("O Bluetooth iniciou como master com sucesso"); // Se o Bluetooth iniciou corretamente, envia a mensagem indicando que o Bluetooth foi configurado como master com sucesso.
  }
  else // Caso a inicialização do Bluetooth falhe.
  {
    Serial.println("Erro ao iniciar o Bluetooth como master"); // Envia uma mensagem indicando que houve um erro ao tentar iniciar o Bluetooth como master.
    Serial.println("O esp32 sera reiniciado em:");             // Envia uma mensagem indicando que o ESP32 será reiniciado em breve.

    for (char i = 5; i < 0; i--) // Um laço que vai de 5 até 1, decrementando o valor de 'i' a cada iteração.
    {
      Serial.printf("%d......\n\r", i); // Exibe no monitor serial a contagem regressiva de 3 a 1, para indicar o tempo até o reinício.
      delay(1000);                      // Aguarda 1 segundo (1000 milissegundos) antes de continuar o laço.
    }

    ESP.restart(); // Reinicia o ESP32 caso a inicialização do Bluetooth como master tenha falhado.
  }
  Serial.println("Tentando conectar ao SLAVE");

  if (BT.connect(enderecoSlave))
  {
    Serial.println("Conectado ao SLAVE com sucesso");
  }
}