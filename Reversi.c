#include <stdio.h>
#include <stdlib.h>
#include "Reversi.h"
#include "raylib.h"
#include <time.h>

#define BoardHeight 720

void RE_startGame(gameRef game){
    printf("Board size: \n");
    scanf("%d", &game->boardSize);
    int size = game->boardSize;
    game->currentPlayer = 1;
    game->tokenColor = 0;
    game->whiteTokens = 0;
    game->blackTokens = 0;
    game->gameEarlyClosed = 0;
    game->separation = BoardHeight / game->boardSize;



    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            game->tokenPosition[i][j] = '0';
        }
    }
    game->tokenPosition[size/2-1][size/2-1] = 'O';
    game->tokenPosition[size/2][size/2] = 'O';
    game->tokenPosition[size/2-1][size/2] = 'X';
    game->tokenPosition[size/2][size/2-1] = 'X';
    game->totalTokens = 4;
}

void RE_showBoard(gameRef game){
    int separation = game->separation;

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        game->column = GetMouseX()/game->separation;
        game->row = GetMouseY()/game->separation;
    }

    BeginDrawing();
    ClearBackground(GRAY);
    DrawRectangle(0,0,BoardHeight, BoardHeight,DARKGREEN);

    for(int i = 1; i < game->boardSize;i++){
        DrawLine(0, separation * i, BoardHeight, separation * i, BLACK);
        DrawLine(separation * i, 0, separation * i, BoardHeight, BLACK);
    }

    for(int i = 0; i < game->boardSize; i++){
        for(int j = 0; j < game->boardSize; j++){
            if(game->tokenPosition[i][j] == 'X'){
                DrawCircle(separation * ((j+1) - 0.5),separation * ((i+1) - 0.5),345/game->boardSize,BLACK);
            }
            else if(game->tokenPosition[i][j] == 'O'){
                DrawCircle(separation * ((j+1) - 0.5),separation * ((i+1) - 0.5),345/game->boardSize,WHITE);
            }
        }
    }

    if(game->currentPlayer){
        DrawText("BLACK", 830, 600, 100, BLACK );
    }
    else{
        DrawText("WHITE", 830, 600, 100, BLACK);
    }

    DrawText(TextFormat("White Tokens: %02i", game->whiteTokens), 730, 60, 20, BLACK);
    DrawText(TextFormat("Black Tokens: %02i", game->blackTokens), 730, 20, 20, BLACK);

    if(RE_winnerCheck(game) > 0 && game->totalTokens == game->boardSize * game->boardSize){
        DrawText(TextFormat("BLACK WINS"), 730, 100, 30, GOLD);
    }
    else if(RE_winnerCheck(game) < 0 && game->totalTokens == game->boardSize * game->boardSize) {
        DrawText(TextFormat("WHITE WINS"), 730, 100, 30, GOLD);
    }
    else if(RE_winnerCheck(game) == 0 && game->totalTokens == game->boardSize * game->boardSize){
        DrawText(TextFormat("DRAW"), 730, 100, 30, GOLD);
    }

    if(game->gameEarlyClosed){
        DrawText(TextFormat("NO MORE MOVES POSSIBLE"), 730, 150, 20, BLACK);
        if(RE_winnerCheck(game) > 0){
            DrawText(TextFormat("BLACK WINS"), 730, 100, 30, GOLD);
        }
        else if(RE_winnerCheck(game) < 0){
            DrawText(TextFormat("WHITE WINS"), 730, 100, 30, GOLD);
        }
        else{
            DrawText(TextFormat("DRAW"), 730, 100, 30, GOLD);
        }
    }


EndDrawing();
}

int RE_getCoord(gameRef game){
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        game->column = GetMouseX()/game->separation;
        game->row = GetMouseY()/game->separation;
        return 1;
    }
    /*printf("\n Enter row: ");
    scanf("%d", &game->row);
    printf("\n enter column: ");
    scanf("%d", &game->column);
    printf("\n");*/
    return 0;
}

/*void RE_showBoard_CMD(gameRef game){
    for(int i = 0;i < 8;i++){
        printf("\n");
        for(int j = 0;j < 8;j++) {
            if(game->tokenPosition[i][j]) {
                printf(" %c ", game->tokenPosition[i][j]);
            }else{
                printf(" - ");
            }
        }
    }
}*/

int RE_winnerCheck(gameRef game){
    return game->blackTokens - game->whiteTokens;
}

void RE_placeToken(gameRef game){
    BeginDrawing();
    if (game->currentPlayer){
        game->tokenPosition[game->row][game->column] = 'X';
    }else{
        game->tokenPosition[game->row][game->column] = 'O';
    }
    game->totalTokens++;
    EndDrawing();
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
                    i++;
                }
                i = 1;
            }
            if(direction->left){    //left flip
                while(game->tokenPosition[row][column - i] == 'O'){
                    game->tokenPosition[row][column - i] = 'X';
                    i++;
                }
                i = 1;
            }
            if(direction->down){    //down flip
                while (game->tokenPosition[row + i][column] == 'O'){
                    game->tokenPosition[row + i][column] = 'X';
                    i++;
                }
                i = 1;
            }
            if(direction->up){      //up flip
                while(game->tokenPosition[row - i][column] == 'O'){
                    game->tokenPosition[row - i][column] = 'X';
                    i++;
                }
                i = 1;
            }
            if(direction->northEast){   //NorthEast flip
                while(game->tokenPosition[row - i][column + i] == 'O'){
                    game->tokenPosition[row - i][column + i] = 'X';
                    i++;
                }
                i = 1;
            }
            if(direction->northWest){   //NorthWest flip
                while(game->tokenPosition[row - i][column - i] == 'O'){
                    game->tokenPosition[row - i][column - i] = 'X';
                    i++;
                }
                i = 1;
            }
            if(direction->southEast){   //SouthEast flip
                while(game->tokenPosition[row + i][column + i] == 'O'){
                    game->tokenPosition[row + i][column + i] = 'X';
                    i++;
                }
                i = 1;
            }
            if(direction->southWest){   //SouthWest flip
                while(game->tokenPosition[row + i][column - i] == 'O'){
                    game->tokenPosition[row + i][column - i] = 'X';
                    i++;
                }
            }
            break;
        case 0:         // O turn
            if(direction->right){   //right flip
                while(game->tokenPosition[row][column+i] == 'X'){
                    game->tokenPosition[row][column+i] = 'O';
                    i++;
                }
                i = 1;
            }
            if(direction->left){    //left flip
                while(game->tokenPosition[row][column - i] == 'X'){
                    game->tokenPosition[row][column - i] = 'O';
                    i++;
                }
                i = 1;
            }
            if(direction->down){    //down flip
                while (game->tokenPosition[row + i][column] == 'X'){
                    game->tokenPosition[row + i][column] = 'O';
                    i++;
                }
                i = 1;
            }
            if(direction->up){      //up flip
                while(game->tokenPosition[row - i][column] == 'X'){
                    game->tokenPosition[row - i][column] = 'O';
                    i++;
                }
                i = 1;
            }
            if(direction->northEast){   //NorthEast flip
                while(game->tokenPosition[row - i][column + i] == 'X'){
                    game->tokenPosition[row - i][column + i] = 'O';
                    i++;
                }
                i = 1;
            }
            if(direction->northWest){   //NorthWest flip
                while(game->tokenPosition[row - i][column - i] == 'X'){
                    game->tokenPosition[row - i][column - i] = 'O';
                    i++;
                }
                i = 1;
            }
            if(direction->southEast){   //SouthEast flip
                while(game->tokenPosition[row + i][column + i] == 'X'){
                    game->tokenPosition[row + i][column + i] = 'O';
                    i++;
                }
                i = 1;
            }
            if(direction->southWest){   //SouthWest flip
                while(game->tokenPosition[row + i][column - i] == 'X'){
                    game->tokenPosition[row + i][column - i] = 'O';
                    i++;
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

int RE_validCheck(gameRef game, directions direction, int row, int column){
    int i = 1;
    int valid;

    RE_directionReset(direction);

    if(game->tokenPosition[row][column] == 'O' || game->tokenPosition[row][column] == 'X'){
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
            i = 1;
            while(game->tokenPosition[row][column - i] == 'O'){     //left check
                i++;
            }
            if (game->tokenPosition[row][column - i] == 'X' && i > 1){
                direction->left = 1;
            }
            i = 1;
            while(game->tokenPosition[row + i][column] == 'O'){     //down check
                i++;
            }
            if(game->tokenPosition[row + i][column] == 'X' && i > 1){
                direction->down = 1;
            }
            i = 1;
            while(game->tokenPosition[row - i][column] == 'O'){     //up check
                i++;
            }
            if(game->tokenPosition[row - i][column] == 'X' && i > 1){
                direction->up = 1;
            }
            i = 1;
            while(game->tokenPosition[row - i][column + i] == 'O'){  //NorthEast Check
                i++;
            }
            if(game->tokenPosition[row - i][column + i] == 'X' && i > 1){
                direction->northEast = 1;
            }
            i = 1;
            while(game->tokenPosition[row- i][column - i] == 'O'){  //NorthWest Check
                i++;
            }
            if(game->tokenPosition[row - i][column - i] == 'X' && i > 1){
                direction->northWest = 1;
            }
            i = 1;
            while(game->tokenPosition[row + i][column + i] == 'O'){  //SouthEast check
                i++;
            }
            if(game->tokenPosition[row + i][column + i] == 'X' && i > 1){
                direction->southEast = 1;
            }
            while(game->tokenPosition[row + i][column - i] == 'O'){ //SouthWest Check
                i++;
            }
            if(game->tokenPosition[row + i][column - i] == 'X' && i > 1){
                direction->southWest = 1;
            }
            break;
        case 0:         //O turn
            while (game->tokenPosition[row][column + i] == 'X') {   //right check
                i++;
            }
            if (game->tokenPosition[row][column + i] == 'O' && i > 1) {
                direction->right = 1;
            }
            i = 1;
            while(game->tokenPosition[row][column - i] == 'X'){     //left check
                i++;
            }
            if (game->tokenPosition[row][column - i] == 'O' && i > 1){
                direction->left = 1;
            }
            i = 1;
            while(game->tokenPosition[row + i][column] == 'X'){     //down check
                i++;
            }
            if(game->tokenPosition[row + i][column] == 'O' && i > 1){
                direction->down = 1;
            }
            i = 1;
            while(game->tokenPosition[row - i][column] == 'X'){     //up check
                i++;
            }
            if(game->tokenPosition[row - i][column] == 'O' && i > 1){
                direction->up = 1;
            }
            i = 1;
            while(game->tokenPosition[row - i][column + i] == 'X'){  //NorthEast Check
                i++;
            }
            if(game->tokenPosition[row - i][column + i] == 'O' && i > 1){
                direction->northEast = 1;
            }
            i = 1;
            while(game->tokenPosition[row- i][column - i] == 'X'){  //NorthWest Check
                i++;
            }
            if(game->tokenPosition[row - i][column - i] == 'O' && i > 1){
                direction->northWest = 1;
            }
            i = 1;
            while(game->tokenPosition[row + i][column + i] == 'X'){  //SouthEast check
                i++;
            }
            if(game->tokenPosition[row + i][column + i] == 'O' && i > 1){
                direction->southEast = 1;
            }
            i = 1;
            while(game->tokenPosition[row + i][column - i] == 'X'){ //SouthWest Check
                i++;
            }
            if(game->tokenPosition[row + i][column - i] == 'O' && i > 1){
                direction->southWest = 1;
            }
            break;
    }
    valid = direction->right + direction->left + direction->down + direction->up;
    valid += direction->northEast + direction->northWest + direction->southEast + direction->southWest;

    return valid;
}

void RE_availableMove(gameRef game, directions direction) {
    game->availableMove = 0;
    for (int i = 0; i < game->boardSize; i++) {
        for (int j = 0; j < game->boardSize; j++) {
            if(RE_validCheck(game, direction, i, j)){
                game->availableMove = 1;
            }
        }
    }
}

void RE_getScore(gameRef game){
    game->blackTokens = 0;
    game->whiteTokens = 0;
    for (int i = 0; i < game->boardSize; i++) {
        for (int j = 0; j < game->boardSize; j++) {
            switch(game->tokenPosition[i][j]){
                case 'X':
                    game->blackTokens++;
                    break;
                case 'O':
                    game->whiteTokens++;
            }
        }
    }
}

void delay(int number_of_seconds){
    int milli_seconds = 100 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}