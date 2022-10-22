/** Autor:
*   Pablo da Silva Marques
*
*   Desenvolvido em 12/10/2022
*/

#include <iostream>
#include <time.h>
#include <game.h>

int main() {
    srand(time(NULL));
    Game snake_game;
    do {
        snake_game.movimento();
        snake_game.exibir();
    } while(snake_game.logica());
    return 0;
}

/*** FIM DO ARQUIVO ***/
