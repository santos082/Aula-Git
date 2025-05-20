#include <Arduino.h>
const int pinBotao = 3;

// prototipos das funcoes( representcao inicial da funcao)
void ligaLed(int); // essa recebe so uma int por que so recebe as entradas dos pinos
void desligaLed(int);
void piscaLed(int, unsigned long); // a piscaLed recebe dois tipo de numaracao 
int somaDeDoisNumeros(int, int); // recebe dois numeros e esses mesmos podem variar, por isso recebe duas int

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  piscaLed(2, 100);
  int resultadoDaSoma = somaDeDoisNumeros(4, 8);
  Serial.println(resultadoDaSoma);
}

void ligaLed(int pin) // nova funcao criada por nos mesmos 
{
  digitalWrite(pin, HIGH);
}
void desligaLed(int pin)
{
  digitalWrite(pin, LOW);
}
void piscaLed(int pin, unsigned long tempo)  // nova funcao criada por nos mesmos 

{
  ligaLed(pin);
  delay(tempo);
  desligaLed(pin);
  delay(tempo);
}

int somaDeDoisNumeros(int numeroA, int numeroB) // nova funcao criada por nos mesmos 

{
  int resultado = numeroA + numeroB;
  return resultado;
}