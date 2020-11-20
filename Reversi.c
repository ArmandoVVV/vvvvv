#include <stdio.h>
#include <stdlib.h>
#include "Reversi.h"

void RE_startGame(gameRef game){
    game->boardSize = 8;
    int size = game->boardSize;
    game->currentPlayer = 1;
    game->userScore = 0;
    game->tokenColor = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            game->tokenPosition[i][j] = 0;
        }
    }

    game->tokenPosition[size/2-1][size/2-1] = 'O';
    game->tokenPosition[size/2][size/2] = 'O';
    game->tokenPosition[size/2-1][size/2] = 'X';
    game->tokenPosition[size/2][size/2-1] = 'X';
    game->totalTokens = 4;
}

void RE_getCoord(gameRef game){
    printf("\n Enter row: ");
    scanf("%d", &game->row);
    printf("\n enter column: ");
    scanf("%d", &game->column);
    printf("\n");
}

void RE_showBoard(gameRef game){
    for(int i = 0;i < game->boardSize;i++){
        printf("\n");
        for(int j = 0;j < game->boardSize;j++) {
            if(game->tokenPosition[i][j]) {
                printf(" %c ", game->tokenPosition[i][j]);
            }else{
                printf(" - ");
            }
        }
    }
}

int RE_winnerCheck(gameRef game){
    int blackTokens = 0;
    int whiteTokens = 0;
    for(int i = 0; i < game->boardSize; i++){
        for(int j = 0; j < game->boardSize; j++){
            if(game->tokenPosition[i][j] == 'O'){
                whiteTokens++;
                }
            else if(game->tokenPosition[i][j] == 'X'){
                blackTokens++;
            }
        }
    }
    return blackTokens - whiteTokens;
}

void RE_placeToken(gameRef game){
    if (game->currentPlayer){
        game->tokenPosition[game->row][game->column] = 'X';
    }else{
        game->tokenPosition[game->row][game->column] = 'O';
    }
    game->totalTokens++;
}

void RE_switchPlayer(gameRef game){
    if(game->tokenColor % 2){
        game->currentPlayer = 1;
    }else{
        game->currentPlayer = 0;
    }
    game->tokenColor++;
}

void RE_flip(gameRef game, directions direction){
    int i = 1;
    int row = game->row;
    int column = game->column;

    switch(game->currentPlayer){
        case 1:         // X turn
            if(direction->right){   //right flip
                while(game->tokenPosition[row][column+i] == 'O'){
                    game->tokenPosition[row][column+i] = 'X';
                }
            }
            break;
        case 0:         // O turn
            if(direction->right){   //right flip
                while(game->tokenPosition[row][column+i] == 'X'){
                    game->tokenPosition[row][column+i] = 'O';
                }
            }
            break;
    }
}

void RE_directionReset(directions direction){
    direction->southWest = 0;
    direction->southEast = 0;
    direction->northWest = 0;
    direction->northEast = 0;
    direction->left = 0;
    direction->right = 0;
    direction->down = 0;
    direction->up = 0;
}

int RE_validCheck(gameRef game, directions direction){
    int i = 1;
    int row = game->row;
    int column = game->column;

    RE_directionReset(direction);

    if(game->tokenPosition[row][column] != 0){
        return 0;
    }
    switch (game->currentPlayer) {
        case 1:         //X turn
            while (game->tokenPosition[row][column + i] == 'O') {   //right check
                i++;
            }
            if (game->tokenPosition[row][column + i] == 'X' && i > 1) {
                direction->right = 1;
            }
            break;
        case 0:         //O turn
            while (game->tokenPosition[row][column + i] == 'X') {   //right check
                i++;
            }
            if (game->tokenPosition[row][column + i] == 'O' && i > 1) {
                direction->right = 1;
            }
            break;
    }
    return direction->right;
}
