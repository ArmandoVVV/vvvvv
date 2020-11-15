#ifndef REVERSI_REVERSI_H
#define REVERSI_REVERSI_H

// BLACK == X == 1
// WHITE == O == 0
struct Game{
    char* tokenPosition[8][8];
    int currentPlayer;
    int userScore;
    int boardSize;
    int tokenColor;
    int totalTokens;
    int y;
    int x;
};
typedef struct Game* gameRef;

void RE_startGame(gameRef);
void RE_showBoard(gameRef);
int RE_winnerCheck(gameRef);
void RE_placeToken(gameRef);
int RE_validCheck(gameRef);

#endif //REVERSI_REVERSI_H
