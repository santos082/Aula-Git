/*
NOME: Guilherme
DATA: 24/03/2025
ATIVIDADE: Continuacao botoes




#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Botao1  0
#define Botao2  145
#define Botao3  329
#define Botao4  505
#define Botao5  741

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.print("> LED A OFF");
  lcd.setCursor(0,1);
  lcd.print("  LED B OFF");
}
void loop()
{
  int Botao = analogRead(A0);
 static bool  posicao = 0;
 /*
  if(Botao >= Botao1 * 0.9 && Botao <= Botao1 * 1.1)
  {
    lcd.setCursor(0,0);
    lcd.print("Boato 1 ligado ");
  }


  if(Botao >= Botao2 * 0.9 && Botao <= Botao2 * 1.1)
  {
    lcd.setCursor(0,0);
    lcd.print("Botao 2 ligado ");
  }


  if(Botao >= Botao3 * 0.9 && Botao <= Botao3 * 1.1)
  {
    lcd.setCursor(0,0);
    lcd.print("Botao 3 ligado ");
  }


  if(Botao >= Botao4 * 0.9 && Botao <= Botao4 * 1.1)
  {
    lcd.setCursor(0,0);
    lcd.print("Botao 4 ligado ");
  }



  if(Botao >= Botao5 * 0.9 && Botao <= Botao5 * 1.1)
  {
    lcd.setCursor(0,0);
    lcd.print("Botao 5 ligado ");
  }


   if(Botao == 1023)
   {
     lcd.setCursor(0,0);
     lcd.print("Botao desligado");
   }

   */

// ******** LCD com 4 if**********
/*
 if (Botao == Botao1 )
 {
   lcd.setCursor(0,0);
   lcd.print(">");
 }

 if (Botao == Botao2 )
 {
   lcd.setCursor(0,0);
   lcd.print("  ");
 }





 if (Botao == Botao2)
 {
   lcd.setCursor(0,1);
   lcd.print(">");
 }

  if (Botao == Botao1)
 {
   lcd.setCursor(0,1);
   lcd.print("  ");
 }


}


//**********LCD com 2 if************

if (Botao == Botao1)
{
  lcd.setCursor(0,0);
  lcd.print(">");
  lcd.setCursor(0,1);
  lcd.print(" ");
}


if (Botao == Botao2)
{
  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.setCursor(0,0);
  lcd.print(" ");
}
}
*/

#include <LiquidCrystal_I2C.h>
#define valorBotao1 0
#define valorBotao2 145
#define valorBotao3 329
#define valorBotao4 505
#define valorBotao5 741
#define valorSolto 1023
#define pinLedA 6
#define pinLedB 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

int intensidadeLedA = 0;
int intensidadeLedB = 0;
int intensidadeLed  = 0;


void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(">LED A OFF");
  lcd.setCursor(0, 1);
  lcd.print(" LED B OFF");
  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);
}

void loop()
{
  int valorLeituraAnalogica = analogRead(A0);
  static int valorAnterior = 1023;
  static bool posicao = 0;
  static bool estadoLedA = 0;
  static bool estadoLedB = 0;
  static bool atualizacao = 0;
  static int resultado = 0;
  //***** TRATAMENTO DOS BOTOES *******
  // NENHUM BOTAO
  if (valorLeituraAnalogica == valorSolto)
  {
  }

  // BOTAO 1 PRESSIONADO
  else if (valorLeituraAnalogica == valorBotao1 &&
           valorAnterior == 1023)
  {
    posicao = 0;
  }

  // BOTAO 2 PRESSIONADO
  else if (valorLeituraAnalogica >= valorBotao2 * 0.9 &&
           valorLeituraAnalogica <= valorBotao2 * 1.1 &&
           valorAnterior == 1023)
  {
    posicao = 1;
    atualizacao = 1;
  }

  // BOTAO 3 PRESSIONADO
  else if (valorLeituraAnalogica >= valorBotao3 * 0.9 &&
           valorLeituraAnalogica <= valorBotao3 * 1.1 &&
           valorAnterior == 1023)
  {
    if(posicao == 0)
    {
    if(intensidadeLedA > 0 && estadoLedA == 1)
    {
      intensidadeLedA -= 10; // se a variavel for menor que 100, ai ela pode somar, so vou subtrair se for maior que zero
      lcd.print(intensidadeLedA);
    } 
    }else{
      if(intensidadeLedB > 0 && estadoLedB == 1)
      {
        intensidadeLedB -= 10;
      }
    }
    atualizacao = 1;
  }

  // BOTAO 4 PRESSIONADO
  else if (valorLeituraAnalogica >= valorBotao4 * 0.9 &&
           valorLeituraAnalogica <= valorBotao4 * 1.1 &&
           valorAnterior == 1023)
  {
    if (posicao == 0)
    {  
      if(intensidadeLedA < 100 && estadoLedA == 1)
      { 
        intensidadeLedA += 10;
       }
    }
    else{
      if (intensidadeLedB <100 && estadoLedB == 1)
      {
        intensidadeLedB +=10;
      }
    }
    atualizacao = 1;
  }

  // BOTAO 5 PRESSIONADO
  else if (valorLeituraAnalogica >= valorBotao5 * 0.9 &&
           valorLeituraAnalogica <= valorBotao5 * 1.1 &&
           valorAnterior == 1023)
  {

    if (posicao == 0)
    {
      estadoLedA = !estadoLedA;
    }
    else
    {
      estadoLedB = !estadoLedB;
    }
  }

  valorAnterior = valorLeituraAnalogica;

  //****** FIM DO TRATAMENTO DOS BOTOES ******

  // ***** ATUALIZA DISPLAY ******
  if (posicao == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print(">");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    
    lcd.setCursor(7, 0);
    
    if (estadoLedA)
    {
      lcd.print(intensidadeLedA);
      lcd.print("        ");
    }
    else
    {
      lcd.print("OFF");
    }
  }

  else
  {
    lcd.setCursor(0, 1);
    lcd.print(">");
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(7, 1);
  
  if (estadoLedB)
  {
    lcd.print(intensidadeLedB);
    lcd.print("   ");
  }
  else
  {
    lcd.print("OFF");
  }
  }
  //***** ATUALIZACAO DOS LED ******
  if (estadoLedA == 1)
  analogWrite(6, intensidadeLedA * 2.55);
  
  else
    digitalWrite(6, LOW);
    
    
  if (estadoLedB == 1)
  analogWrite(5, intensidadeLedB * 2.55);
  
  else
    digitalWrite(5, LOW);
  
  atualizacao = 0;
}
