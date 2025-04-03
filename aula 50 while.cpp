/*
NOME: Guilherme
DATA: 02/04/2025
ATIVIDADE: piscar led com While
*/

#include <Arduino.h>
#define botao 0
#define pinLed 2

void setup()
{
  delay(2000);
  pinMode(pinLed, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  Serial.begin(9600);

  while (digitalRead(0) == 0)
  {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }
}

void loop()
{
}
