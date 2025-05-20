/*
NOME: Guilherme
DATA: 19/05/2025
PROJETO:  Programação Orientada a Objetos
*/

#include <Arduino.h>
#include "Led.h"

Led ledESP(4);
Led ledVermelho (2);
Led ledAmarelo (5);
Led ledBranco (21);


void setup()
{
  ledESP.piscar(2);
  ledVermelho.piscar(8);
  ledAmarelo.piscar(5);
  ledBranco.piscar (6);
}

void loop()
{
  ledESP.update();
  ledVermelho.update();
  ledAmarelo.update();
  ledBranco.update();

  
}