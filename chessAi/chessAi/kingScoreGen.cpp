// kingScoreGen.cpp tallies the score of a king on a specific square, and returns that score
// as an int to a total board score.

#include <iostream>

using namespace std;

// Function declarations.
int getKingPositionScore(int location, int color, bool endGame);
int getKingDefendedValue(int location);
int getKingAttackedValue(int location);
int findNumberOfMoves(int location);
int isCastlePossible(int color);

// Functions from board.cpp
int getTopColor();
bool getEndGame();
bool getBlackCastle();
bool getWhiteCastle();

// Functions from threatChecker.cpp
int getPiecesThatProtect(int location);
int getPiecesThatThreaten(int location);

// Functions from moveGenerator.cpp
int numMovesAvailable(int location);

// Main function that is called by the
// board score generator.  Location is
// the square number of the piece.
// Color is the color of the King that is
// in the square.
int generateKingScore(int location, int color){

    int score = 0;
    int kingScore = 32676;
    bool endGame = getEndGame();

    score += kingScore;
    score += getKingPositionScore(location, color, endGame);
    score += getKingDefendedValue(location);
    score -= getKingAttackedValue(location);
    score += findNumberOfMoves(location);
    score += isCastlePossible(color);

    return score;
}

int findNumberOfMoves(int location){
    int tempNum = numMovesAvailable(location);

    if(tempNum < 2){
        return -5;
    }
    else{
        return 0;
    }
}

int isCastlePossible(int color){
    int score;

    if(color == 0){
        if(getWhiteCastle() == false){
            score = 0;
        }
        else{
            score = -30;
        }
    }
    else{
        if(getBlackCastle() == false){
            score = 0;
        }
        else{
            score = -30;
        }
    }

    return score;
}

int getKingPositionScore(int location, int color, bool endGame){

    int tColor = getTopColor();

    if(color == tColor){
        if(endGame == false){
            int updatedScoreTable[8][8] = {
                20,  30,  10,   0,   0,  10,  30,  20,
                20,  20,   0,   0,   0,   0,  20,  20,
                -10, -20, -20, -20, -20, -20, -20, -10,
                -20, -30, -30, -40, -40, -30, -30, -20,
                -30, -40, -40, -50, -50, -40, -40, -30,
                -30, -40, -40, -50, -50, -40, -40, -30,
                -30, -40, -40, -50, -50, -40, -40, -30,
                -30, -40, -40, -50, -50, -40, -40, -30
                                };
            int row = location / 8;
            int col = location % 8;

            return updatedScoreTable[row][col];
        }
        else{
            int updatedScoreTable[8][8] = {
                -50,-30,-30,-30,-30,-30,-30,-50
                -30,-30,  0,  0,  0,  0,-30,-30,
                -30,-10, 20, 30, 30, 20,-10,-30,
                -30,-10, 30, 40, 40, 30,-10,-30,
                -30,-10, 30, 40, 40, 30,-10,-30,
                -30,-10, 20, 30, 30, 20,-10,-30,
                -30,-20,-10,  0,  0,-10,-20,-30,
                -50,-40,-30,-20,-20,-30,-40,-50,
                                };
            int row = location / 8;
            int col = location % 8;

            return updatedScoreTable[row][col];
        }
    }
    else{
        if(endGame == false){
            int updatedScoreTable[8][8] = {
                -30, -40, -40, -50, -50, -40, -40, -30,
                -30, -40, -40, -50, -50, -40, -40, -30,
                -30, -40, -40, -50, -50, -40, -40, -30,
                -30, -40, -40, -50, -50, -40, -40, -30,
                -20, -30, -30, -40, -40, -30, -30, -20,
                -10, -20, -20, -20, -20, -20, -20, -10,
                20,  20,   0,   0,   0,   0,  20,  20,
                20,  30,  10,   0,   0,  10,  30,  20
                            };
            int row = location / 8;
            int col = location % 8;
            return updatedScoreTable[row][col];
        }
        else{
            int updatedScoreTable[8][8] = {
                -50,-40,-30,-20,-20,-30,-40,-50,
                -30,-20,-10,  0,  0,-10,-20,-30,
                -30,-10, 20, 30, 30, 20,-10,-30,
                -30,-10, 30, 40, 40, 30,-10,-30,
                -30,-10, 30, 40, 40, 30,-10,-30,
                -30,-10, 20, 30, 30, 20,-10,-30,
                -30,-30,  0,  0,  0,  0,-30,-30,
                -50,-30,-30,-30,-30,-30,-30,-50
                            };
            int row = location / 8;
            int col = location % 8;
            return updatedScoreTable[row][col];
        }
    }
}

int getKingDefendedValue(int location){

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
int getKingAttackedValue(int location){

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
