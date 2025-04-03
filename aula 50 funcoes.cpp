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
  int resultadoDaSoma = somaDeDoisNumeros(4, 8); //* aqui usamos uma funcao dentro de outra funcao 
  Serial.println(resultadoDaSoma);
}


//* void- significa uma funcao vazia



void ligaLed(int pin) // nova funcao criada por nos mesmos, feita para ligar os leds que forem determinados 
{
  digitalWrite(pin, HIGH);
}
void desligaLed(int pin) // esse larinha pode ser chamado de argumentos, e ou argumentos  
{
  digitalWrite(pin, LOW);
}
void piscaLed(int pin, unsigned long tempo)  // nova funcao criada por nos mesmos, feita para piscar o led

{
  ligaLed(pin);
  delay(tempo);
  desligaLed(pin);
  delay(tempo);
}

int somaDeDoisNumeros(int numeroA, int numeroB) // nova funcao criada por nos mesmos, feita para somar doois numeros 

{
  int resultado = numeroA + numeroB;
  return resultado;
}