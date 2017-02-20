// pawnScoreGen.cpp tallies the score of a pawn on a specific square, and returns that score
// as an int to a total board score.

#include <iostream>

using namespace std;

// Function declarations.
int getPositionScore(int location, int color);
int getDefendedValue(int location);
int getAttackedValue(int location);

// Functions from board.cpp
int getTopColor();

// Functions from threatChecker.cpp
int getPiecesThatProtect(int location);
int getPiecesThatThreaten(int location);

// Sets the top color.
int tColor = getTopColor();

// The main function that gets called by the
// board score generator.  Location is the
// square number of the piece.
int generatePawnScore(int location, int color){

    int score = 0;
    int pawnScore = 100;

    score += pawnScore;
    score += getPositionScore(location, color);
    score += getDefendedValue(location);
    score -+ getAttackedValue(location);

    return score;
}

int getPositionScore(int location, int color){

    if(color != tColor){
         int updatedScoreTable[8][8] = {
                            0, 0, 0, 0, 0, 0, 0, 0,
                            5, 10, 10, -25, -25, 10, 10, 5,
                            5, -5, -10, 0, 0, -10, -5, 5,
                            0, 0, 0, 25, 25, 0, 0, 0,
                            5, 5, 10, 27, 27, 10, 5, 5,
                            10, 10, 20, 30, 30, 20, 10, 10,
                            50, 50, 50, 50, 50, 50, 50, 50,
                            0, 0, 0, 0, 0, 0, 0, 0
                            };
        int row = location / 8;
        int col = location % 8;
        return updatedScoreTable[row][col];
    }
    else{
        int updatedScoreTable[8][8] = {
                            0, 0, 0, 0, 0, 0, 0, 0,
                            50, 50, 50, 50, 50, 50, 50, 50,
                            10, 10, 20, 30, 30, 20, 10, 10,
                            5, 5, 10, 27, 27, 10, 5, 5,
                            0, 0, 0, 25, 25, 0, 0, 0,
                            5, -5, -10, 0, 0, -10, -5, 5,
                            5, 10, 10, -25, -25, 10, 10, 5,
                            0, 0, 0, 0, 0, 0, 0, 0
                            };
            int row = location / 8;
            int col = location % 8;
            return updatedScoreTable[row][col];
    }
}

// Returns the value gained by the piece being defended by
// specific pieces.
int getDefendedValue(int location){

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
int getAttackedValue(int location){

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
