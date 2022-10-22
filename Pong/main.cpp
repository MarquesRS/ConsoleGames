/** Autor:
*   Pablo da Silva Marques
*
*   Desenvolvido em 12/10/2022
*/

#include <iostream>
#include "game.h"
#include <thread>
#include <windows.h>

void movimento_thread(Game* pong_game, bool player) {
    pong_game->movimento_barra(player);
    pong_game->movimento_bola();
    pong_game->logica();
}

int main() {
    srand(time(NULL));
    Game pong_game;
    do {
        std::thread player1(movimento_thread, &pong_game, true);
        std::thread player2(movimento_thread, &pong_game, false);
        player1.join();
        player2.join();
        pong_game.exibir();
    } while(true);
    return 0;
}

/*** FIM DO ARQUIVO ***/
