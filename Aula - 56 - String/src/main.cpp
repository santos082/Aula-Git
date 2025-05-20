#include <Arduino.h>

// FORMAS DE ESCREVER PALAVRAS EM C

char palavra[10] = "OLA MUNDO";
char palavra2[10] = {'O', 'L', 'A', ' ', 'M', 'U', 'N', 'D', 'O', '\0'};

String palavra3 = "Hoje eh quinta";

void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.println(palavra);
  Serial.println(palavra2);

  strcpy(palavra, "SENAI");

  if (strcmp(palavra, "SENAI") == 0) // Se for igual Retorna
  {
    Serial.println("SAO IGAUIS");
  }
  if (strncmp(palavra2, "OLA", 3) == 0)

  {
    Serial.println("As primeiras letras da palavra eh OLA");
  }

  if (strstr(palavra2, "MUNDO"))
  {
    Serial.println("Palavra MUNDO detectada");
  }

  //* -----------------------------------------------------------------------------------

  Serial.println(palavra3.length());         // retorna o numero de letras do objeto da classe string
  Serial.println(palavra3.charAt(5));        // retorna a quinta posicao da palavra
  Serial.println(palavra3.substring(3, 11)); // retorna da terceira ah decima primeira posicao 👌
  Serial.println(palavra3.indexOf('u'));     // retorna a posicao da ocorrencia da primeira letra procurada
  Serial.println(palavra3.lastIndexOf('e')); // retorna a posicao da ultima ocorrencia da letra procurada
  if (palavra3.equals("Hoje eh quinta"))     // retorna verdadeiro se forem iguais
    Serial.println("Sao iguais");

  if (palavra3.equalsIgnoreCase("hoje Eh quinta")) // retorna verdadeiro e falsa se forem iguais ignorando as letras minusculas e/ou maiusculas
    Serial.println(" Sao igauis ");

    if(palavra3.startsWith ("Hoje")) // retorna verdadeiro se apalavra comecar com o determinado texto
    Serial.println("comeca com Hoje");

    if(palavra3.endsWith("inta")) // retorna verdadeiro s a palavra terminar com determinado texto
    Serial.println("termina com inta");

    String valor ="123";
    int valorNumero = valor.toInt(); // usando o toint, é possivel retornar o valor do texto para o valor numerico / de 123 texto para 123 numer

    String valor2 ="10.5";
    float valorNumerico2 = valor2.toFloat();

    String mensagem = "valor = 50";

    int tamanho = mensagem.length(); // medir o tamanho do texto 
    String extracao = mensagem.substring(8, tamanho); // extrair o numero iniciando em uma posicao conhecida até i fim do texto 
    Serial.println(tamanho);
    Serial.println(extracao); 

    int numero = extracao.toInt(); // tranforme o conteudo extraido em um numero inteiro 
    Serial.println(numero * 2); // utilize o numero sem moderacao... HAHAHA

    //! CONTINUANDO 
    palavra3.toLowerCase(); // alterar todas as letras para minusculas 
    Serial,println(palavra3);
    palavra3.toUpperCase(); // alterar todas para maiisculas 
    Serial.println(palavra3);  

String textoLed = "Led = on";
Serial.println(textoLed);
textoLed.replace("ON" , "OFF"); // Substitui uma palavra no ytexto por outra 
Serial.println(textoLed);  // "Led = Off";

String novafrase = "Texto    "; // varios espacos 
novafrase.trim(); // remove os espacos do fim do texto 

novafrase.concat( "adicionado"); // adiciona um texto a string 
Serial.println(novafrase);


}

void loop()
{
}
