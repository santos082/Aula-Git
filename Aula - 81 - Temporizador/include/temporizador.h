#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

class Temporizador
{
private:

    int pino;

bool ativo;

unsigned long tempo_ms = 1000;
unsigned long intervalo;
unsigned long inicio;
unsigned long ultimoTempo;




public:
Temporizador(unsigned long tempo_ms = 1000);

    void iniciar();
    void parar();
    void reiniciar();
    void definirIntervalo(unsigned long tempo_ms);
    bool estaAtivo();
    bool estaPronto();
};




#endif