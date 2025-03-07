/*
NOME:Guilherme 
DATA:07/03/2025
ATIVIDADE:Fazer Led piscar sem daley
*/
#define pinLedVerde 13

unsigned long tempoInicial = 0;
bool estadoLed = 1; 


void setup()
{
 pinMode(pinLedVerde, OUTPUT);
}

void loop()
{
  unsigned long tempoAtual = millis();

  if(tempoAtual - tempoInicial >= 1000){
    
  if(estadoLed){
    digitalWrite(pinLedVerde, LOW);
    estadoLed = 0;
  
  }else{
    digitalWrite(pinLedVerde, HIGH);
    estadoLed = 1;
    
    }
  	tempoInicial = tempoAtual; 
  
  }
  
}