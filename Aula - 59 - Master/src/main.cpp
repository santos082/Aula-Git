/*
NOME: Guilherme
DATA: 15/03/2025
*/
#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial BT;

uint8_t endSlave[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // vetor para comunicaçao

void setup()
{
  Serial.begin(9600);

  //!                     ↓ indica que é master
  if(BT.begin("EspGui", true))
  { 
    Serial.println("Bluetooth iniciado com sucesso");
  }
  else
  {
    Serial.print("Erro ao iniciar o Bluetooth");
  }

  if (BT.connect(endSlave)) // serve para ver se um disposito se conectou com o outro, e retorna 1 ou 0
  {
    Serial.println("Conectado com sucesso");
  }
  else
  {
    Serial.println("Nao foi possível conectar o dispositovo Bluetooth");
  }

  
  Serial.println(BT.getBtAddressString()); // mostra o endereço fisico do Blutoofh
}

void loop()
{
  if (Serial.available()) // se tiver alguma coisa no serial
  {
    String mensagemEnviar = Serial.readStringUntil('\n'); // leia   uma mensagem   ate que tenha um enter
    mensagemEnviar.trim();                                // tira o quem ao final, \n \r...b
    BT.println(mensagemEnviar);
  }

  if (BT.available())
  {
    String mensagemRecebida = BT.readStringUntil('\n');
    mensagemRecebida.trim();
    Serial.println("Mensagem Recebida" + mensagemRecebida);

    if (mensagemRecebida.equals("liga"))
    {
    }

    else if (mensagemRecebida.equals("desliga"))
      {
      }
  }
}