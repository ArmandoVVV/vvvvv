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


    while(game->totalTokens < game->boardSize * game->boardSize  && !WindowShouldClose()) {
        RE_showBoard(game);

        RE_availableMove(game, direction);
        RE_getScore(game);

        if (game->availableMove ){
            if (RE_getCoord(game)) {
                printf("usuario selecciono %d %d\n", game->row, game->column);
                if (RE_validCheck(game, direction, game->row, game->column)) {
                    RE_placeToken(game);
                    RE_flip(game, direction);
                    RE_switchPlayer(game);
                } else {
                    printf("El movimiento fue falso\n");

                }
            }
        }else{
            RE_switchPlayer(game);
            RE_availableMove(game, direction);
            printf("Cambio de turno por falta de movimientos\n");
            if(!game->availableMove){
                game->gameEarlyClosed = 1;
                RE_showBoard(game);
                for (int i = 0; i < 10; i++) {
                    delay(3);
                }
                CloseWindow();
                return 0;
            }
        }
    }
    RE_getScore(game);
    RE_showBoard(game);
    for (int i = 0; i < 10; i++) {
        delay(5);
    }
    CloseWindow();
    return 0;
}
