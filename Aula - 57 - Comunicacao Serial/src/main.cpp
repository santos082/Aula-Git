/*
NOME: Guilherme
DATA: 11/03/2025
*/

#include <Arduino.h>
#define pinLed 2
void setup()
{
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
}

void loop()
{

  static bool estadoLed = false;
  static bool pisca = false;
  static int velocidade = 1000;

  if (Serial.available())
  {
    String texto = Serial.readStringUntil('\n');
    Serial.printf("Voce digitou: %s\n\r", texto);
    texto.trim();

    if (texto.equals("liga"))
    {
      estadoLed = true;
      pisca = false;
    }
    else if (texto.equals("desliga"))
    {
      estadoLed = false;
      pisca = false;
    }

    else if (texto.equals("pisca"))
    {
      pisca = true;
    }
    else if (texto.equals("mais rapido "))
    {
      pisca = true;
      velocidade -= 100;
      if (velocidade < 50)
      {
        velocidade = 50;
      }
      
    }

    else if (texto.equals("mais devagar"))
    {
      pisca = true;
      velocidade += 100;
      if (velocidade > 1000)
      {
        velocidade = 1000;
      }
      
    }

    else if (texto.startsWith("velocidade = "))
    {
      int tamanho = texto.length();
      String extracao = texto.substring(13, tamanho);
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

    else
    {
      Serial.println("comando nao encontrado");
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

//****** LER APENAS UM CARACTER *******

// void loop()
// {
//   if (Serial.available()) // fala se tem algo na serial ou nao //****** buffer-  é um espaço de memória temporário que armazena dados antes de processá-los ou enviá-los
//   {
//     char caracter = Serial.read();
//     Serial.printf("Recebido letra: %c\n\r", caracter);

//     if (caracter == 'a')
//     {
//       digitalWrite(pinLed, HIGH);
//     }

//     else if (caracter == 'b')
//     {
//       digitalWrite(pinLed, LOW);
//     }
//   }
// }