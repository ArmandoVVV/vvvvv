#include <stdlib.h>
#include <stdio.h>
#include "Reversi.h"
#include "raylib.h"

#define WindowWidth 1280
#define WindowHeight 720

int main() {
    gameRef game = malloc(sizeof(struct Game));
    directions direction = malloc(sizeof(struct FlipDirection));

    RE_startGame(game);

    InitWindow(WindowWidth,WindowHeight,"Reversi");

    SetTargetFPS(60);


    while(game->totalTokens < game->boardSize * game->boardSize && !WindowShouldClose()) {
        RE_showBoard(game);
        //RE_showBoard_CMD(game);
        int userClick = RE_getCoord(game);

        if (userClick) {
            userClick = 0;
            printf("usuario selecciono %d %d\n", game->row, game->column);

            if(RE_validCheck(game, direction)){
                RE_placeToken(game);
                RE_flip(game, direction);
                RE_switchPlayer(game);
            }else{
                printf("El movimiento fue falso\n");

            }
        }
        /*if(game->currentPlayer){
            printf("X turn   ");
        }else{
            printf("O turn   ");
        }
        printf("    %d : %d  ", game->totalTokens, game->boardSize * game->boardSize);
    }
    if(RE_winnerCheck(game) > 0){
        printf("\n Black wins (X)");
    }else{
        printf("\n White wins (O)");*/
    }
    CloseWindow();
    return 0;
}
