#ifndef REVERSI_REVERSI_H
#define REVERSI_REVERSI_H

// BLACK == X == 1
// WHITE == O == 0
struct Game{
    char tokenPosition[20][20];
    int currentPlayer;
    int boardSize;
    int tokenColor;
    int totalTokens;

    int column;
    int row;

    int separation;

    int availableMove;
    int blackTokens;
    int whiteTokens;

    int gameEarlyClosed;
    int CPU;
};
typedef struct Game* gameRef;

struct FlipDirection{
    int right;
    int left;
    int up;
    int down;
    int northWest;
    int northEast;
    int southWest;
    int southEast;
};
typedef struct FlipDirection* directions;

void RE_startGame(gameRef);
void RE_showBoard(gameRef);
void RE_showBoard_CMD(gameRef);
int RE_winnerCheck(gameRef);
void RE_placeToken(gameRef);
int RE_validCheck(gameRef, directions, int row, int column);
int RE_getCoord(gameRef, directions);
void RE_flip(gameRef, directions);
void RE_switchPlayer(gameRef);
void RE_directionReset(directions);
void RE_availableMove(gameRef, directions);
void RE_getScore(gameRef);

void RE_saveGame(gameRef);
void RE_resumeGame(gameRef);

void delay(int number_of_seconds);

#endif //REVERSI_REVERSI_H
