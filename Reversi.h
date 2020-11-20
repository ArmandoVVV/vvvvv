#ifndef REVERSI_REVERSI_H
#define REVERSI_REVERSI_H

// BLACK == X == 1
// WHITE == O == 0
struct Game{
    char tokenPosition[8][8];
    int currentPlayer;
    int userScore;
    int boardSize;
    int tokenColor;
    int totalTokens;
    int column;
    int row;
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
int RE_winnerCheck(gameRef);
void RE_placeToken(gameRef);
int RE_validCheck(gameRef, directions);
void RE_getCoord(gameRef);
void RE_flip(gameRef, directions);
void RE_switchPlayer(gameRef);
void RE_directionReset(directions);

#endif //REVERSI_REVERSI_H
