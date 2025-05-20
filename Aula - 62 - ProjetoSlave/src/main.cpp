#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial BT;


void setup() 
{
  Serial.begin(9600);
  BT.begin("ESP32-Slave");
  Serial.println(BT.getBtAddressString());
}

void loop() 
{
if (BT.available())
{
  String payload = BT.readStringUntil('\n');
  payload.trim();
  Serial.println(payload);
}

}
