/** Autor:
*   Pablo da Silva Marques
*
*   Desenvolvido em 12/10/2022
*/

#ifndef GAME_H
#define GAME_H

#include <vector>

const unsigned int TAM_LINHA = 26;
const unsigned int TAM_COLUNA = 58;

enum {STOP, W, D, S, A};

struct Corpo {
    unsigned int linha;
    unsigned int coluna;
    unsigned int linha_anterior = 0;
    unsigned int coluna_anterior = 0;
};

struct Cabeca {
    unsigned int linha = TAM_LINHA / 2;
    unsigned int coluna = TAM_COLUNA / 2;
    unsigned int direcao = STOP;
    std::vector<Corpo> corpo;
};

class Game {
private:
    Cabeca cobra;
    unsigned int fruta_linha;
    unsigned int fruta_coluna;
    unsigned int pontuacao_atual;
    unsigned int melhor_pontuacao;

public:
    Game();
    void exibir();
    bool movimento();
    bool logica();
    void escrever_placar();
    unsigned int ler_placar();
    void reiniciar();
    void visibilidade_cursor(bool cursor = false);
    void posicao_cursor(int x = 0, int y = 0);
};

#endif // GAME_H

/*** FIM DO ARQUIVO ***/
