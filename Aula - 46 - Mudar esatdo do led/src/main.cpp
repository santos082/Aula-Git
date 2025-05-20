#include <Arduino.h>
/*

NOME: Guilherme 
ATIVIDADE: trata,ento do botao 



*/


#define pinLed 2
#define pinButton 5
unsigned long tempoInicial = 0;
int estadoAnterior = HIGH ;
bool estadoBotao = 0 ;

void setup()
{
    pinMode(pinLed, OUTPUT);
    pinMode(pinButton, INPUT_PULLUP);
    Serial.begin(9600);
}
 
void loop()
{
    //* decta mudanca no estado do botao
    bool estadoAtualBotao = digitalRead (pinButton);
    static bool estadoAnteriorBotao = 1;
    static bool ultimaAcao = 1;

    static unsigned long tempoUltimaAlteracao = 0; 
    unsigned long tempoAtual = millis();
    const unsigned long tempoFiltro = 50;

    static bool estadoLed = 0;
    
    //! INICIA O TRATAMENTO DE RUIDO DO BOTAO

    // * Dettecta mudanca no estado do botato 
    if (estadoAtualBotao != estadoAnteriorBotao)
    {
      tempoUltimaAlteracao = tempoAtual; //* Atualiza o tempo da ultima mudanca 
    }
    
    //* Verifica se o novo estado se manteve estavel por tempo suficiente 
    if ((tempoAtual - tempoUltimaAlteracao)> tempoFiltro)
    {
        //* Verifica se ainda nao processamos essa nova acao 
        if (estadoAtualBotao != ultimaAcao)
        {
            ultimaAcao = estadoAtualBotao; //* Atualiza o estado ja procesado para evitar acoes repetidas 

            //* se o botao foi pressinado(nivel logico LOW)
            if (!estadoAtualBotao)
            {
                estadoLed = !estadoLed;
                digitalWrite(pinLed, estadoLed);
            }
            //* se o botao foi solto (nivel logico HIGH), nenhuma acao por enquanto 
            else
            {
            }
            
        }
        
    }
    //* Atualiza o estado anterior para a proxima iteracao 
    estadoAnteriorBotao = estadoAtualBotao;
    //! FINAL DO TRATAMENTO DO BOTAO 
    
}