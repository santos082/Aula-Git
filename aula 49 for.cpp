#include <Arduino.h>
#define pinLed 2
#define pinBoot 23

int vetor[5] = {10, 20, 30, 40, 50};

void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinBoot, INPUT_PULLUP);
  Serial.begin(9600);

  int tabuada = 0;
  int resultado = 0;

  for (int j = 0; j < 11; j++)
  {
    for (int i = 0; i < 11; i++)
    {
      Serial.printf("%d x %d = %d \n\r", j, i, i * j);
    }
    Serial.println("----------------------");
  }
}

void loop()
{
}