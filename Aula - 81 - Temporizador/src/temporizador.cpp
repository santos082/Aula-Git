#include "temporizador.h"
#include <Arduino.h>

/**
 * @brief Construtoe da classe temporizador
 *
 * @param tempo tempo no qual ocorre o temporizador
 */
Temporizador::Temporizador(unsigned long tempo_ms)
{
    intervalo = tempo_ms;
    inicio= 0;
    ativo = false;

}

/**
 * @brief inicializa o temporizador
 *
 */
void Temporizador::iniciar()
{
    ultimoTempo = millis();
    ativo = true;
}

/**
 * @brief Para o temporizador
 */
void Temporizador::parar()
{
    ativo = false;
}

/**
 * @brief Reinicia o temporizador
 */
void Temporizador::reiniciar()
{
    ultimoTempo = millis();
    ativo = true;
}

/**
 * @brief Retorna true se o intervalo tiver passado desde o iniciar().
 */
bool Temporizador::estaPronto()
{

    if (!ativo)return false;

    return (millis() - ultimoTempo >= intervalo);
}

/**
 * @brief Retorna true se estiver ativo.
 */
bool Temporizador::estaAtivo()
{
    return ativo = true;
}

/**
 * @brief Altera o intervalo
 */
void Temporizador::definirIntervalo(unsigned long tempo_ms)
{
intervalo = tempo_ms;
}