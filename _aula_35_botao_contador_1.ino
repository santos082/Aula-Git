/*
NOME: Guiulherme
DATA: 12/03/2025
ATIVIDADE: botao contador 

*/

#define Botao 9

int estadoAnterior = LOW; // Estado anterior do botão
int estadoBotao = 0;        // Contador de cliques


void setup() {
    Serial.begin(9600);
    pinMode(Botao, INPUT);
}

void loop() {
 
    int estadoAtual = digitalRead(Botao);
    if (estadoAtual == HIGH && estadoAnterior == LOW) {
        estadoBotao++;
        Serial.print("Botao esta em: ");
        Serial.println(estadoBotao);
    }
    estadoAnterior = estadoAtual;
}