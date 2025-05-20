#include <Arduino.h>
#include <BluetoothSerial.h>
// porta 6

#define pinLed 2

BluetoothSerial BT;

void setup()
{
  pinMode(pinLed, OUTPUT);

  BT.begin("ESPNino");
}

void loop()
{
  static bool estadoLed = false;

  if (BT.available())
  {
    String mensagem = BT.readStringUntil('\n');
    mensagem.trim();

    if (mensagem.equals("liga"))
    {
      estadoLed = true;
      BT.println("Led ligado");
    }
    if (mensagem.equals("desliga"))
    {
      estadoLed = false;
      BT.println("Led Desligado");
    }
  }
}
