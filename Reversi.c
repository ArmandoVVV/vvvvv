#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reversi.h"

void RE_startGame(gameRef game){
    game->boardSize = 8;
    int size = game->boardSize;
    game->currentPlayer = 0;
    game->userScore = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            game->tokenPosition[i][j] = NULL;
        }
    }

    game->tokenPosition[size/2-1][size/2-1] = "O";
    game->tokenPosition[size/2][size/2] = "O";
    game->tokenPosition[size/2-1][size/2] = "X";
    game->tokenPosition[size/2][size/2-1] = "X";
    game->totalTokens = 4;

}

void RE_getCoord(gameRef game){
    printf("\n Enter X: ");
    scanf("%d", &game->x);
    printf("\n enter Y: ");
    scanf("%d", &game->y);
    printf("\n");
}

void RE_showBoard(gameRef game){
    for(int i = 0;i < game->boardSize;i++){
        printf("\n");
        for(int j = 0;j < game->boardSize;j++) {
            if(game->tokenPosition[i][j]) {
                printf(" %s ", game->tokenPosition[i][j]);
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
            if(game->tokenPosition[i][j] == "O"){
                whiteTokens++;
                }
            else if(game->tokenPosition[i][j] == "X"){
                blackTokens++;
            }
        }
    }
    if(blackTokens > whiteTokens){
        return 1;
    }else if(blackTokens < whiteTokens){
        return 0;
    }else{
        return 2;
    }
}

void RE_placeToken(gameRef game){
    if (game->tokenColor % 2){
        game->currentPlayer = 1;
        game->tokenPosition[game->y][game->x] = "X";
    }else{
        game->currentPlayer = 0;
        game->tokenPosition[game->y][game->x] = "O";
    }
    game->totalTokens = game->totalTokens + 1;
    game->tokenColor = game->tokenColor + 1;
}

int RE_validCheck(gameRef game){
    int i;
    if(game->currentPlayer == 0){   //X turn
        i = 1;          //right check
        while(game->tokenPosition[game->x][game->y+i] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x][game->y+i] == "X" && i != 1){
            return 1;
        }
        i = 1;          //left check
        while(game->tokenPosition[game->x][game->y-i] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x][game->y-i] == "X" && i != 1){
            return 1;
        }
        i = 1;          //Up check
        while(game->tokenPosition[game->x-i][game->y] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y] == "X" && i != 1){
            return 1;
        }
        i = 1;          //Down check
        while(game->tokenPosition[game->x+i][game->y] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y] == "X" && i != 1){
            return 1;
        }
        i = 1;          //NorthEast check
        while(game->tokenPosition[game->x-i][game->y+i] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y+i] == "X" && i != 1){
            return 1;
        }
        i = 1;          //NorthWest check
        while(game->tokenPosition[game->x-i][game->y-i] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y-i] == "X" && i != 1){
            return 1;
        }
        i = 1;          //SouthEast check
        while(game->tokenPosition[game->x+i][game->y+i] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y+i] == "X" && i != 1){
            return 1;
        }
        i = 1;          //SouthWest check
        while(game->tokenPosition[game->x+i][game->y-i] == "O"){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y-i] == "X" && i != 1){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(game->currentPlayer){
        i = 1;          //right check
        while(game->tokenPosition[game->x][game->y+i] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x][game->y+i] == "O" && i != 1){
            return 1;
        }
        i = 1;          //left check
        while(game->tokenPosition[game->x][game->y-i] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x][game->y-i] == "O" && i != 1){
            return 1;
        }
        i = 1;          //Up check
        while(game->tokenPosition[game->x-i][game->y] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y] == "O" && i != 1){
            return 1;
        }
        i = 1;          //Down check
        while(game->tokenPosition[game->x+i][game->y] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y] == "O" && i != 1){
            return 1;
        }
        i = 1;          //NorthEast check
        while(game->tokenPosition[game->x-i][game->y+i] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y+i] == "O" && i != 1){
            return 1;
        }
        i = 1;          //NorthWest check
        while(game->tokenPosition[game->x-i][game->y-i] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y-i] == "O" && i != 1){
            return 1;
        }
        i = 1;          //SouthEast check
        while(game->tokenPosition[game->x+i][game->y+i] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y+i] == "O" && i != 1){
            return 1;
        }
        i = 1;          //SouthWest check
        while(game->tokenPosition[game->x+i][game->y-i] == "X"){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y-i] == "O" && i != 1){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}
