#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reversi.h"

int main() {
    gameRef game = malloc(sizeof(struct Game));
    directions direction  =malloc(sizeof(struct FlipDirection));
    RE_startGame(game);
    RE_showBoard(game);
    printf("X turn");

    while(game->totalTokens < game->boardSize * game->boardSize){
        RE_getCoord(game);
        if(RE_validCheck(game, direction)){
            RE_placeToken(game);
            RE_flip(game, direction);
        }
        RE_showBoard(game);
        if(game->currentPlayer){
            printf("O turn   ");
        }else{
            printf("X turn   ");
        }
        printf("    %d : %d  ", game->totalTokens, game->boardSize * game->boardSize);

    }
    printf("\n winner: %d", RE_winnerCheck(game));
    return 0;
}
