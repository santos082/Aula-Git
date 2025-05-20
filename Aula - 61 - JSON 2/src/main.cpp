#include <Arduino.h>
#include <ArduinoJson.h>

JsonDocument doc;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    deserializeJson(doc, msg);

    if(!do)

    float temperatura = doc["temperatura"];
    int umidade = doc["umidade"];
    int botao = doc["precionamentos"];
    String estados = doc["estados"];


    printf("A temperatura é : %f\n\r", temperatura);
    printf("A umidade esta : %d%\n\r", umidade);
    printf("A estado esta : %s\n\r", estados);
    printf("O botao foi precionado :  %d vezes\n\r" , botao);
  }
}