#include "botao.h"
/**
 * @brief Construtoe da classe botao
 *
 * @param p numero do pino digital ao qual o botao esta conectado
 */
botao::botao(uint8_t p) : pino(p) {}

/**
 * @brief inicializa o botao
 *
 * Configura o pino como entrada. O metodo pull-up padrao
 *
 */

void botao::begin()
{
    pinMode(pino, INPUT_PULLUP);
    estadoAtual = digitalRead(pino);
    estadoAnterior = estadoAtual;
    estadoConfirmado = estadoAtual;
    tempoInicioEstado = millis();
}

/**
 * @brief Define o tempo de filtro (debounce) para estabilizar as leituras do botao
 *
 * @param tempo Tempo de debounce em milissegundos
 */
void botao::configuraFiltro(unsigned long tempo)
{
    tempoFiltro = tempo;
}


/**
 * @brief Atualiza o estado interno do botao 
 * 
 * Deve ser chamado frequentimente dentro do loop principal
 * Decta mudanca de estado e acina as flags internas de evenentos
 * (pressionado, solto, mudanca de estado)
 */
void botao::update()
{
    unsigned long agora = millis();
    estadoAtual = digitalRead(pino);
    flagAlteracao = false;
    flagPressionado = false;
    flagSolto = false;

    if (estadoAtual != estadoAnterior)
        tempoUltimaMudanca = agora;
    if ((agora - tempoUltimaMudanca) >= tempoFiltro)
    {
        if (estadoAtual != estadoConfirmado)
        {
            estadoConfirmado = estadoAtual;
            duracaoEstado = agora - tempoInicioEstado;
            tempoInicioEstado = agora;
            flagAlteracao = true;

            if (!estadoAtual) //* Botao Pressionado
            {
                flagPressionado = true;
            }
            else //* Botao Solto
            {
                flagSolto = true;
            }
        }
    }
    estadoAnterior = estadoAtual;
}

/**
 * @brief Verifica se o botao acabou de ser pressionado
 * 
 * 
 * @return true se houver uma ttransicao para o estado pressinado
 * na ultima atualizacao 
 */
bool botao::pressionado()
{
    return flagPressionado;
}
/**
 * @brief verifica se o botao acabou de ser solto
 * 
 * @return true se houve uma trancisao para o estado soltona
 * ultima atualizacao 
 */
bool botao::solto()
{
    return flagSolto;    
}


/**
 * @brief Verifica se houve uma mudanca de estado no botao
 * 
 * @return true  se o estado do botapo mudou (pressionado, solto)
 * ultima atualizacao 
 */
bool botao::alteracaoEstado()
{
    return flagAlteracao;
}

/**
 * @brief Retona a duracao do ultimo estado mantido (pressionado ou solto)
 * 
 * @return Tempo em millissegundos que o botao permaneceu no ultimo estado
 */
unsigned long botao::duracaoUltimoEstado()
{
    return duracaoEstado;
}