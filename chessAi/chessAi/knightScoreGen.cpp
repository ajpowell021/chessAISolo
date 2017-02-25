// knightScoreGen.cpp tallies the score of a knight on a specific square, and returns that score
// as an int to a total board score.

#include <iostream>

using namespace std;

// Function declarations.
int getKnightPositionScore(int location, int color);
int getKnightDefendedValue(int location);
int getKnightAttackedValue(int location);

// Functions from board.cpp
int getTopColor();
bool getEndGame();

// Functions from threatChecker.cpp
int getPiecesThatProtect(int location);
int getPiecesThatThreaten(int location);

// Sets the top color.

// Main function that is called by the
// board score generator.  Location is
// the square number of the piece.
// Color is the color of the knight that is
// in the square.
int generateKnightScore(int location, int color){

    int score = 0;
    int knightScore = 320;

    score += knightScore;
    score += getKnightPositionScore(location, color);
    score += getKnightDefendedValue(location);
    score -= getKnightAttackedValue(location);

    if(getEndGame() == true){
        score -= 10;
    }

    return score;
}

int getKnightPositionScore(int location, int color){

    int tColor = getTopColor();

    if(color != tColor){
        int updatedScoreTable[8][8] = {
                            -50, -40, -20, -30, -30, -20, -40, -50,
                            -40, -20, 0, 5, 5, 0, -20, -40,
                            -30, 5, 10, 15, 15, 10, 5, -30,
                            -30, 0, 15, 20, 20, 15, 0, -30,
                            -30, 5, 15, 20, 20, 15, 5, -30,
                            -30, 0, 10, 15, 15, 10, 0, -30,
                            -40, -20, 0, 0, 0, 0, -20, -40,
                            -50, -40, -30, -30, -30, -30, -40, -50
                            };
        int row = location / 8;
        int col = location % 8;

        return updatedScoreTable[row][col];
    }
    else{
        int updatedScoreTable[8][8] = {
                            -50, -40, -30, -30, -30, -30, -40, -50,
                            -40, -20, 0, 0, 0, 0, -20, -40,
                            -30, 0, 10, 15, 15, 10, 0, -30,
                            -30, 5, 15, 20, 20, 15, 5, -30,
                            -30, 0, 15, 20, 20, 15, 0, -30,
                            -30, 5, 10, 15, 15, 10, 5, -30,
                            -40, -20, 0, 5, 5, 0, -20, -40,
                            -50, -40, -20, -30, -30, -20, -40, -50
                        };
        int row = location / 8;
        int col = location % 8;
        return updatedScoreTable[row][col];
    }
}

int getKnightDefendedValue(int location){

    int defendNum = getPiecesThatProtect(location);

    int kingProtects = defendNum / 100000;
    defendNum -= kingProtects * 100000;
    int queenProtects = defendNum / 10000;
    defendNum -= queenProtects * 10000;
    int bishopProtects = defendNum / 1000;
    defendNum -= bishopProtects * 1000;
    int knightProtects = defendNum / 100;
    defendNum -= knightProtects * 100;
    int rookProtects = defendNum / 10;
    defendNum -= rookProtects * 10;
    int pawnProtects = defendNum / 1;

    int total = (kingProtects) + (queenProtects) + (rookProtects * 2) + (bishopProtects * 3) +
                (knightProtects * 3) + (pawnProtects * 6);

    return total;
}

// Returns the value gained by the piece being
//attacked by specific pieces.
int getKnightAttackedValue(int location){

    int defendNum = getPiecesThatThreaten(location);

    int kingProtects = defendNum / 100000;
    defendNum -= kingProtects * 100000;
    int queenProtects = defendNum / 10000;
    defendNum -= queenProtects * 10000;
    int bishopProtects = defendNum / 1000;
    defendNum -= bishopProtects * 1000;
    int knightProtects = defendNum / 100;
    defendNum -= knightProtects * 100;
    int rookProtects = defendNum / 10;
    defendNum -= rookProtects * 10;
    int pawnProtects = defendNum / 1;

    int total = (kingProtects) + (queenProtects) + (rookProtects * 2) + (bishopProtects * 3) +
                (knightProtects * 3) + (pawnProtects * 6);

    return total;
}
