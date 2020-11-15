#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reversi.h"

int main() {
    gameRef game = malloc(sizeof(struct Game));
    RE_startGame(game);
    RE_showBoard(game);

    while(game->totalTokens < game->boardSize * game->boardSize){
        printf("\n Enter X: ");
        scanf("%d", &game->x);
        printf("\n enter Y: ");
        scanf("%d", &game->y);
        printf("\n");

        if(RE_validCheck(game)){
            RE_placeToken(game);
        }
        RE_showBoard(game);
        printf("    %d : %d  ", game->totalTokens, game->boardSize * game->boardSize);
    }
    printf("\n winner: %d", RE_winnerCheck(game));
    return 0;
}