/*
NOME: Guilherme
DATA: 03/04/2025
ATIVIDADE:



*/

#include <Arduino.h>

float pitagoras(float, float);
float formulafahrenheit(float);
float tranformacao (float);
float tamanhotv(float);
void setup()
{
  Serial.begin(9600);
  // float hipotenusa = pitagoras(3, 4);    
  // Serial.println(hipotenusa);

  //float conta = formulafahrenheit(50); *******A*******
  //Serial.println(conta);

 // float polegadas = conversao(2); *******B*******
 // Serial.println(polegadas);

 //float centimetros = tv(42);  *******C*******
 // Serial.println(centimetros);

float desafio = tamanhotv (72); //************** D ************
Serial.println(desafio);


}

void loop()
{
}

float pitagoras(float catetoA, float catetoB)
{
  float resultado = sq(catetoA) + sq(catetoB);
  return sqrt(resultado);
}

float formulafahrenheit(float graus)
{
  float fahrenheit((graus * 9 / 5) + 32);
  return fahrenheit;
}

float transformacao  (float milimetros)
{
float polegada = (milimetros / 25.4);
return polegada;
}

float tv (float polegadas)
{
float centimetros = ( polegadas * 2.54);
return centimetros;

}

float tamanhotv( float altura)
{
float conversao = sq(tv(50)) -sq(altura) ;
return  sqrt(conversao);

}




//************* FORMA DO PROF atividade1 ***********

/*
float hipotenusa(float,float);

void setup()
{
Serial.begin(9600);
float numero1 = hipotenusa(2.5 , 3.5)
}
void loop()
{
}

float hipotenusa(float catetoA, float catetoB)
{
 return sqrt(sq(catetoA)+ sq(catetoB));
}


*/