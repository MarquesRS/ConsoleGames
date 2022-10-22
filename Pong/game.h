/** Autor:
*   Pablo da Silva Marques
*
*   Desenvolvido em 12/10/2022
*/

#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <time.h>

const unsigned int TAM_LINHA = 27;
const unsigned int TAM_COLUNA = 58;

// Diagonal inferior Direita
// Diagonal inferior esquerda
// Diagonal Superior Esquerda
// Diagonal superior Direita
enum {ESQUERDA, DIREITA, DID, DIE, DSE, DSD};

struct Bola {
    unsigned int linha = TAM_LINHA / 2;
    unsigned int coluna = TAM_COLUNA / 2;
    unsigned int direcao = ESQUERDA;

    void reiniciar(int direcao) volatile {
        this->linha = TAM_LINHA / 2;
        this->coluna = TAM_COLUNA / 2;
        this->direcao = direcao;
    }
};

struct Barra {
    unsigned int coluna;
    unsigned int linha_superior = (TAM_LINHA / 2) - 1;
    unsigned int linha_meio = TAM_LINHA / 2;
    unsigned int linha_inferior = (TAM_LINHA / 2) + 1;
};

class Game {
private:
    unsigned int vitorias_1;
    unsigned int vitorias_2;
    unsigned int pontuacao_1;
    unsigned int pontuacao_2;

public:
    volatile Bola * bola = new Bola;
    volatile Barra * barra1 = new Barra;
    volatile Barra  * barra2 = new Barra;

    Game();
    void exibir();
    void movimento_bola();
    void movimento_barra(bool player);
    bool logica();
    void visibilidade_cursor(bool cursor = false);
    void posicao_cursor(int x = 0, int y = 0);
};

#endif // GAME_H

/*** FIM DO ARQUIVO ***/
