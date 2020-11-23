#include <stdio.h>
#include <stdlib.h>
#include "Reversi.h"

int main() {
    gameRef game = malloc(sizeof(struct Game));
    directions direction  =malloc(sizeof(struct FlipDirection));
    RE_startGame(game);
    RE_showBoard(game);

    while(game->totalTokens < game->boardSize * game->boardSize){
        RE_getCoord(game);
        if(RE_validCheck(game, direction)){
            RE_placeToken(game);
            RE_flip(game, direction);
            RE_switchPlayer(game);
        }
        RE_showBoard(game);
        if(game->currentPlayer){
            printf("X turn   ");
        }else{
            printf("O turn   ");
        }
        printf("    %d : %d  ", game->totalTokens, game->boardSize * game->boardSize);

    }
    if(RE_winnerCheck(game) > 0){
        printf("\n Black wins (X)");
    }else{
        printf("\n White wins (O)");
    }
    return 0;
}
