/** Autor:
*   Pablo da Silva Marques
*
*   Desenvolvido em 12/10/2022
*/

#include "game.h"
#include <fstream>
#include <windows.h>
#include <iostream>

Game::Game() {
    this->fruta_linha = (TAM_LINHA / 2) - 5;
    this->fruta_coluna = TAM_COLUNA / 2;
    this->pontuacao_atual = 0;
    this->melhor_pontuacao = this->ler_placar();
    this->visibilidade_cursor();
}

void Game::exibir() {
    this->posicao_cursor();
    Sleep(50);
    bool continuar;
    std::cout << std::endl;
    for (unsigned int linha = 0; linha < TAM_LINHA; linha++) {
        std::cout << "  ";
        for (unsigned int coluna = 0; coluna < TAM_COLUNA; coluna++) {
            continuar = true;
            // Corpo da cobra. Se a posicão bater, continue no laço
            for (unsigned long int corpo_indice = 0; corpo_indice < this->cobra.corpo.size(); corpo_indice++) {
                if ((this->cobra.corpo[corpo_indice].linha == linha) && (this->cobra.corpo[corpo_indice].coluna == coluna)) {
                    std::cout << char(219) << char(219);
                    continuar = false;
                    break;
                }
            }
            if (continuar) {
                // (Paredes nos limites do mapa) || (Cabeça da cobra) || (Fruta)
                if ( (linha == 0 || coluna == 0 || linha == TAM_LINHA-1 || coluna == TAM_COLUNA-1)
                  || ((this->cobra.linha == linha) && (this->cobra.coluna == coluna) )
                  || ((this->fruta_linha == linha)  && (this->fruta_coluna == coluna))
                   )
                {
                    std::cout << char(219) << char(219);
                }
                // Chão
                else {
                    std::cout << "  ";
                }
            }
        }
        std::cout<<std::endl;
    }
    std::cout << std::endl;
    std::cout << "  Melhor pontuacao: " << this->melhor_pontuacao << " | Pontuacao atual: " << this->pontuacao_atual << std::endl;
}

bool Game::movimento(){
    // Muda a direção se uma tecla for pressionada
    if (GetAsyncKeyState('W')) {
        this->cobra.direcao = W;
    }
    else if (GetAsyncKeyState('D')) {
        this->cobra.direcao = D;
    }
    else if (GetAsyncKeyState('S')) {
        this->cobra.direcao = S;
    }
    else if (GetAsyncKeyState('A')) {
        this->cobra.direcao = A;
    }
    // Enquanto tiver corpo, atualiza a posição atual para a posição da cabeça
    if (!this->cobra.corpo.empty()) {
        for (unsigned long int linha = 0; linha < this->cobra.corpo.size(); linha++) {
            if (linha == 0) {
                this->cobra.corpo[linha].linha_anterior = this->cobra.corpo[linha].linha;
                this->cobra.corpo[linha].coluna_anterior = this->cobra.corpo[linha].coluna;
                this->cobra.corpo[linha].linha = this->cobra.linha;
                this->cobra.corpo[linha].coluna = this->cobra.coluna;
            }
            else {
                this->cobra.corpo[linha].linha_anterior = this->cobra.corpo[linha].linha;
                this->cobra.corpo[linha].coluna_anterior = this->cobra.corpo[linha].coluna;
                this->cobra.corpo[linha].linha = this->cobra.corpo[linha-1].linha_anterior;
                this->cobra.corpo[linha].coluna = this->cobra.corpo[linha-1].coluna_anterior;
            }
        }
    }
    // Cabeça se reposiciona constantemente de acordo com a direção
    switch (cobra.direcao) {
        case W:
            cobra.linha--;
        break;
        case D:
            cobra.coluna++;
        break;
        case S:
            cobra.linha++;
        break;
        case A:
            cobra.coluna--;
        break;
    }

    // Inverte direção ao atingir limite do mapa
    if (cobra.linha == 0) {
        cobra.linha = TAM_LINHA-2;
        cobra.direcao = W;
    }
    else if (cobra.linha == TAM_LINHA-1) {
        cobra.linha = 1;
        cobra.direcao = S;
    }
    else if (cobra.coluna == 0) {
        cobra.coluna = TAM_COLUNA-2;
        cobra.direcao = A;
    }
    else if (cobra.coluna == TAM_COLUNA-1) {
        cobra.coluna = 1;
        cobra.direcao = D;
    }
    return true;
}

bool Game::logica() {
    // Bateu no corpo, fim de jogo
    for (unsigned long int corpo_indice = 0; corpo_indice < this->cobra.corpo.size(); corpo_indice++) {
        if ((this->cobra.corpo[corpo_indice].linha == this->cobra.linha) && (this->cobra.corpo[corpo_indice].coluna == this->cobra.coluna)) {
            system("cls");
            std::cout << std::endl << "  FIM DE JOGO " << std::endl << std::endl;
            if (this->pontuacao_atual > this->melhor_pontuacao) {
                this->melhor_pontuacao = pontuacao_atual;
                this->escrever_placar();
            }
            this->reiniciar();
            system("pause");
            system("cls");
            return true;
        }
    }
    // Comeu a fruta, gera nova fruta, adiciona corpo a lista e aumenta a pontuação
    if ((this->cobra.linha == this->fruta_linha) && (this->cobra.coluna == this->fruta_coluna)) {
        bool gerarNovo = false;
        do {
            this->fruta_linha = 3 + rand() % (TAM_LINHA-6);
            this->fruta_coluna = 3 + rand() % (TAM_COLUNA-6);
            for (unsigned long int corpo_indice = 0; corpo_indice < this->cobra.corpo.size(); corpo_indice++) {
                if (this->fruta_linha == this->cobra.corpo[corpo_indice].linha && this->fruta_coluna == this->cobra.corpo[corpo_indice].coluna) {
                    gerarNovo = true;
                }
            }
            if ((this->fruta_linha == this->cobra.linha) && (this->fruta_coluna == this->cobra.coluna)) {
                gerarNovo = true;
            }
        } while (gerarNovo);
        Corpo corpo;
        if (this->cobra.corpo.empty()) {
            corpo.linha = this->cobra.linha;
            corpo.coluna = this->cobra.coluna;
        }
        else {
            corpo.linha = this->cobra.corpo.end()->linha;
            corpo.coluna = this->cobra.corpo.end()->coluna;
        }
        this->cobra.corpo.push_back(corpo);
        this->pontuacao_atual = this->pontuacao_atual + 10;
    }
    return true;
}

void Game::escrever_placar() {
    std::ofstream arquivo;
    arquivo.open("placar.txt");
    if (arquivo.is_open()) {
        arquivo << this->pontuacao_atual;
        arquivo.close();
    }
}

unsigned int Game::ler_placar() {
    std::string placar = "";
    std::fstream arquivo;
    arquivo.open("placar.txt", std::ios::in);
    if (arquivo.is_open()) {
        getline(arquivo, placar);
        arquivo.close();
        return std::stoi(placar);
    }
    return 0;
}

void Game::reiniciar() {
    this->fruta_linha = (TAM_LINHA / 2) - 5;
    this->fruta_coluna = TAM_COLUNA / 2;
    this->pontuacao_atual = 0;
    this->cobra.linha = TAM_LINHA / 2;
    this->cobra.coluna = TAM_COLUNA / 2;
    this->cobra.direcao = STOP;
    this->cobra.corpo.clear();
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
