#include <stdio.h>
#include <stdlib.h>
#include "Reversi.h"

void RE_startGame(gameRef game){
    game->boardSize = 8;
    int size = game->boardSize;
    game->currentPlayer = 0;
    game->userScore = 0;

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
    game->tokenColor = 1;
    if (game->tokenColor % 2){
        game->currentPlayer = 1;
        game->tokenPosition[game->y][game->x] = 'X';
    }else{
        game->currentPlayer = 0;
        game->tokenPosition[game->y][game->x] = 'O';
    }
    game->totalTokens = game->totalTokens + 1;
    game->tokenColor = game->tokenColor + 1;
}

void RE_flip(gameRef game, directions direction){
    int i = 1;
    switch(game->currentPlayer){
        case 0:         // X turn
            if(direction->right){
                while(game->tokenPosition[game->x][game->y+i] == 'X'){
                    game->tokenPosition[game->x][game->y+i] = 'O';
                }
                i = 1;
            }
            if(direction->left){
                while(game->tokenPosition[game->x][game->y-i] == 'O'){
                    game->tokenPosition[game->x][game->y-i] = 'X';
                }
                i = 1;
            }
            if(direction->up){
                while(game->tokenPosition[game->x-i][game->y] == 'O'){
                    game->tokenPosition[game->x-i][game->y] = 'X';
                }
                i = 1;
            }
            if(direction->down){
                while(game->tokenPosition[game->x+i][game->y] == 'O'){
                    game->tokenPosition[game->x+i][game->y] = 'X';
                }
                i = 1;
            }
            if(direction->northEast){
                while(game->tokenPosition[game->x-i][game->y+i] == 'O'){
                    game->tokenPosition[game->x-i][game->y+i] = 'X';
                }
                i = 1;
            }
            if(direction->northWest){
                while(game->tokenPosition[game->x-i][game->y-i] == 'O'){
                    game->tokenPosition[game->x-i][game->y-i] ='X';
                }
                i = 1;
            }
            if(direction->southEast){
                while(game->tokenPosition[game->x+i][game->y+i] == 'O'){
                    game->tokenPosition[game->x+i][game->y+i] = 'X';
                }
                i = 1;
            }
            if(direction->southWest){
                while(game->tokenPosition[game->x+i][game->y-i] == 'O'){
                    game->tokenPosition[game->x+i][game->y-i] = 'X';
                }
            }
            break;
        case 1:         // O turn
            if(direction->right){
                while(game->tokenPosition[game->x][game->y+i] == 'X'){
                    game->tokenPosition[game->x][game->y+i] = 'O';
                }
                i = 1;
            }
            if(direction->left){
                while(game->tokenPosition[game->x][game->y-i] == 'X'){
                    game->tokenPosition[game->x][game->y-i] = 'O';
                }
                i = 1;
            }
            if(direction->up){
                while(game->tokenPosition[game->x-i][game->y] == 'X'){
                    game->tokenPosition[game->x-i][game->y] = 'O';
                }
                i = 1;
            }
            if(direction->down){
                while(game->tokenPosition[game->x+i][game->y] == 'X'){
                    game->tokenPosition[game->x+i][game->y] = 'O';
                }
                i = 1;
            }
            if(direction->northEast){
                while(game->tokenPosition[game->x-i][game->y+i] == 'X'){
                    game->tokenPosition[game->x-i][game->y+i] = 'O';
                }
                i = 1;
            }
            if(direction->northWest){
                while(game->tokenPosition[game->x-i][game->y-i] == 'X'){
                    game->tokenPosition[game->x-i][game->y-i] = 'O';
                }
                i = 1;
            }
            if(direction->southEast){
                while(game->tokenPosition[game->x+i][game->y+i] == 'X'){
                    game->tokenPosition[game->x+i][game->y+i] = 'O';
                }
                i = 1;
            }
            if(direction->southWest){
                while(game->tokenPosition[game->x+i][game->y-i] == 'X'){
                    game->tokenPosition[game->x+i][game->y-i] = 'O';
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
    int i;
    RE_directionReset(direction);
    if(game->tokenPosition[game->x][game->y] != 0){
        return 0;
    }
    if(game->currentPlayer == 0){   //X turn
        i = 1;          //right check
        while(game->tokenPosition[game->x][game->y+i] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x][game->y+i] == 'X' && i != 1){
            direction->right = 1;
        }
        i = 1;          //left check
        while(game->tokenPosition[game->x][game->y-i] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x][game->y-i] == 'X' && i != 1){
            direction->left = 1;
        }
        i = 1;          //Up check
        while(game->tokenPosition[game->x-i][game->y] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y] == 'X' && i != 1){
            direction->up = 1;
        }
        i = 1;          //Down check
        while(game->tokenPosition[game->x+i][game->y] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y] == 'X' && i != 1){
            direction->down = 1;
        }
        i = 1;          //NorthEast check
        while(game->tokenPosition[game->x-i][game->y+i] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y+i] == 'X' && i != 1){
            direction->northEast = 1;
        }
        i = 1;          //NorthWest check
        while(game->tokenPosition[game->x-i][game->y-i] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y-i] == 'X' && i != 1){
            direction->northWest = 1;
        }
        i = 1;          //SouthEast check
        while(game->tokenPosition[game->x+i][game->y+i] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y+i] == 'X' && i != 1){
            direction->southEast = 1;
        }
        i = 1;          //SouthWest check
        while(game->tokenPosition[game->x+i][game->y-i] == 'O'){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y-i] == 'X' && i != 1){
            direction->southWest = 1;
        }
    }
    else if(game->currentPlayer){
        i = 1;          //right check
        while(game->tokenPosition[game->x][game->y+i] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x][game->y+i] == 'O' && i != 1){
            direction->right = 1;
        }
        i = 1;          //left check
        while(game->tokenPosition[game->x][game->y-i] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x][game->y-i] == 'O' && i != 1){
            direction->left = 1;
        }
        i = 1;          //Up check
        while(game->tokenPosition[game->x-i][game->y] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y] == 'O' && i != 1){
            direction->up = 1;
        }
        i = 1;          //Down check
        while(game->tokenPosition[game->x+i][game->y] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y] == 'O' && i != 1){
            direction->down = 1;
        }
        i = 1;          //NorthEast check
        while(game->tokenPosition[game->x-i][game->y+i] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y+i] == 'O' && i != 1){
            direction->northEast = 1;
        }
        i = 1;          //NorthWest check
        while(game->tokenPosition[game->x-i][game->y-i] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x-i][game->y-i] == 'O' && i != 1){
            direction->northWest = 1;
        }
        i = 1;          //SouthEast check
        while(game->tokenPosition[game->x+i][game->y+i] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y+i] == 'O' && i != 1){
            direction->southEast = 1;
        }
        i = 1;          //SouthWest check
        while(game->tokenPosition[game->x+i][game->y-i] == 'X'){
            i++;
        }
        if(game->tokenPosition[game->x+i][game->y-i] == 'O' && i != 1){
            direction->southWest = 1;
        }
    }
    int valid = direction->northWest + direction->northEast + direction->southEast + direction->southWest;
    valid = valid + direction->up + direction->down + direction->right + direction->left;
    return valid;
}
