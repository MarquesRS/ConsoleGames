/** Autor:
*   Pablo da Silva Marques
*
*   Desenvolvido em 12/10/2022
*/

#include "game.h"
#include <windows.h>
#include <iostream>

Game::Game() {
    this->visibilidade_cursor();
    this->barra1->coluna = 2;
    this->barra2->coluna = TAM_COLUNA-3;
    this->vitorias_1 = 0;
    this->vitorias_2 = 0;
    this->pontuacao_1 = 0;
    this->pontuacao_2 = 0;
}

void Game::exibir() {
    this->posicao_cursor();
    for (unsigned int linha = 0; linha < TAM_LINHA; linha++) {
        std::cout << "  ";
        for (unsigned int coluna = 0; coluna < TAM_COLUNA; coluna++) {
            // (Teto || Chão) || (Meio) || (Bola) || (Personagem)
            if ( ((linha == 0) || (linha == TAM_LINHA-1))
              || ((coluna == TAM_COLUNA / 2) && (linha % 2 == 0))
              || (((linha == this->barra1->linha_superior) || (linha == this->barra1->linha_meio) || (linha == this->barra1->linha_inferior)) && (coluna == this->barra1->coluna))
              || (((linha == this->barra2->linha_superior) || (linha == this->barra2->linha_meio) || (linha == this->barra2->linha_inferior)) && (coluna == this->barra2->coluna))
              || ((linha == this->bola->linha) && (coluna == this->bola->coluna))
               )
            {
                std::cout << char(219) << char(219);
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "      Pontuacao 1: " << this->pontuacao_1 << " | Pontuacao 2: " << this->pontuacao_2;
    std::string espaco = "                                                ";
    std::cout << espaco << "Vitorias 1: " << this->vitorias_1 << " | Vitorias 2: " << this->vitorias_2 << std::endl;
}

void Game::movimento_barra(bool player) {
    if (player) {
        if (GetAsyncKeyState('W')) {
            if (this->barra1->linha_superior > 1) {
                this->barra1->linha_superior--;
                this->barra1->linha_inferior--;
                this->barra1->linha_meio--;
            }
        }
        else if (GetAsyncKeyState('S')) {
            if (this->barra1->linha_inferior < TAM_LINHA-2) {
                this->barra1->linha_superior++;
                this->barra1->linha_inferior++;
                this->barra1->linha_meio++;
            }
        }
    }
    else {
        if (GetAsyncKeyState('I')) {
            if (this->barra2->linha_superior > 1) {
                this->barra2->linha_superior--;
                this->barra2->linha_inferior--;
                this->barra2->linha_meio--;
            }
        }
        else if (GetAsyncKeyState('K')) {
            if (this->barra2->linha_inferior < TAM_LINHA-2) {
                this->barra2->linha_superior++;
                this->barra2->linha_inferior++;
                this->barra2->linha_meio++;
            }
        }
    }
}

void Game::movimento_bola() {
    // Movimenta a bola baseado na direção
    switch(this->bola->direcao) {
        case ESQUERDA:
            this->bola->coluna--;
        break;
        case DIREITA:
            this->bola->coluna++;
        break;
        case DID:
            this->bola->linha--;
            this->bola->coluna++;
        break;
        case DIE:
            this->bola->linha--;
            this->bola->coluna--;
        break;
        case DSE:
            this->bola->linha++;
            this->bola->coluna--;
        break;
        case DSD:
            this->bola->linha++;
            this->bola->coluna++;
        break;
    }
}

bool Game::logica() {
    // Bola atingiu o teto ou o chão
    if ((this->bola->linha == 0) || (this->bola->linha == TAM_LINHA-1)) {
        switch (this->bola->direcao) {
            case DID:
                this->bola->direcao=DSD;
            break;
            case DIE:
                this->bola->direcao=DSE;
            break;
            case DSE:
                this->bola->direcao=DIE;
            break;
            case DSD:
                this->bola->direcao=DID;
            break;
        }
    }
    // Bola passou o limite
    else if (this->bola->coluna == 0) {
        this->pontuacao_2++;
        if (this->pontuacao_2 == 10) {
            this->vitorias_2++;
            this->pontuacao_2 = 0;
        }
        this->bola->reiniciar(DIREITA);
    }
    else if (this->bola->coluna == TAM_COLUNA-1) {
        this->pontuacao_1++;
        if (this->pontuacao_1 == 10) {
            this->vitorias_1++;
            this->pontuacao_1 = 0;
        }
        this->bola->reiniciar(ESQUERDA);
    }
    // Bola atingiu o meio da barra
    else if ( ((this->bola->coluna == this->barra1->coluna) && (this->bola->linha == this->barra1->linha_meio))
           || ((this->bola->coluna == this->barra2->coluna) && (this->bola->linha == this->barra2->linha_meio))
            )
    {
        if (this->bola->direcao == ESQUERDA || this->bola->direcao == DIE || this->bola->direcao == DSE) {
            this->bola->direcao = DIREITA;
        }
        else {
            this->bola->direcao = ESQUERDA;
        }
    }
    // Bola atingiu a parte superior da barra
    else if ( ((this->bola->coluna == this->barra1->coluna) && (this->bola->linha == this->barra1->linha_superior))
           || ((this->bola->coluna == this->barra2->coluna) && (this->bola->linha == this->barra2->linha_superior))
            )
    {
        if (this->bola->direcao == ESQUERDA || this->bola->direcao == DIE || this->bola->direcao == DSE) {
            this->bola->direcao = DID;
        }
        else {
            this->bola->direcao = DIE;
        }
    }
    // Bola atingiu a parte inferior da barra
    else if ( ((this->bola->coluna == this->barra1->coluna) && (this->bola->linha == this->barra1->linha_inferior))
           || ((this->bola->coluna == this->barra2->coluna) && (this->bola->linha == this->barra2->linha_inferior))
            )
    {
        if (this->bola->direcao == ESQUERDA || this->bola->direcao == DIE || this->bola->direcao == DSE) {
            this->bola->direcao = DSD;
        }
        else {
            this->bola->direcao = DSE;
        }
    }
    return true;
}

void Game::visibilidade_cursor(bool cursor) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = cursor;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Game::posicao_cursor(int x, int y) {
    COORD cursor;
    cursor.X = x;
    cursor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

/*** FIM DO ARQUIVO ***/
