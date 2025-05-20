/*
NOME: Guilherme
DATA: 12/03/2025
ATIVIDADE: led/botao 
*/
#define Botao 10
#define pinLed 2 

int estadoAnterior = HIGH;
int estadoBotao = 0;
int estadoLed = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(Botao, INPUT);
  pinMode(pinLed, OUTPUT);
}

void loop()
{
  int estadoAtual = digitalRead(Botao);
  if (estadoAtual == HIGH && estadoAnterior == LOW){
     estadoBotao++;
     estadoLed = !estadoLed;
     digitalWrite(pinLed, estadoLed);
  }
  estadoAnterior = estadoAtual;
}