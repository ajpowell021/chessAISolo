// bishopScoreGen.cpp tallies the score of a bishop on a specific square, and returns that score
// as an int to a total board score.

#include <iostream>

using namespace std;

// Function declarations.
int getBishopPositionScore(int location, int color);
int getBishopDefendedValue(int location);
int getBishopAttackedValue(int location);
int getDoubleBishops(int color);

// Functions from board.cpp
int getTopColor();
bool getEndGame();
int getPieceType(int location);

// Functions from threatChecker.cpp
int getPiecesThatProtect(int location);
int getPiecesThatThreaten(int location);

// Main function that is called by the
// board score generator.  Location is
// the square number of the piece.
// Color is the color of the bishop that is
// in the square.
int generateBishopScore(int location, int color){

    int score = 0;
    int bishopScore = 325;

    score += bishopScore;
    score += getBishopPositionScore(location, color);
    score += getBishopDefendedValue(location);
    score -= getBishopAttackedValue(location);
    score += getDoubleBishops(color);

    if(getEndGame() == true){
        score += 10;
    }

    return score;
}

int getBishopPositionScore(int location, int color){

    int tColor = getTopColor();

    if(color != tColor){
        int updatedScoreTable[8][8] = {
            
                -20,-10,-10,-10,-10,-10,-10,-20,
                -10,  0,  0,  0,  0,  0,  0,-10,
                -10,  0,  5, 10, 10,  5,  0,-10,
                -10,  5,  5, 10, 10,  5,  5,-10,
                -10,  0, 10, 10, 10, 10,  0,-10,
                -10, 10, 10, 10, 10, 10, 10,-10,
                -10,  5,  0,  0,  0,  0,  5,-10,
                -20,-10,-40,-10,-10,-40,-10,-20
                            };
        int row = location / 8;
        int col = location % 8;

        return updatedScoreTable[row][col];
    }
    else{
        int updatedScoreTable[8][8] = {

                -20,-10,-40,-10,-10,-40,-10,-20
                -10,  5,  0,  0,  0,  0,  5,-10,
                -10, 10, 10, 10, 10, 10, 10,-10,
                -10,  0, 10, 10, 10, 10,  0,-10,
                -10,  5,  5, 10, 10,  5,  5,-10,
                -10,  0,  5, 10, 10,  5,  0,-10,
                -10,  0,  0,  0,  0,  0,  0,-10,
                -20,-10,-10,-10,-10,-10,-10,-20,
                };
        int row = location / 8;
        int col = location % 8;
        return updatedScoreTable[row][col];
    }
}

int getBishopDefendedValue(int location){

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
int getBishopAttackedValue(int location){

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

// Returns 10 points if player has both bishops.
int getDoubleBishops(int color){

    int tempPieceId;
    int bishopNumber;
    for(int i = 0; i < 64; i++){
        if(color == 0){
            tempPieceId = getPieceType(i);
            if(tempPieceId == 4){
                bishopNumber++;
            }
        }
        else{
            tempPieceId = getPieceType(i);
            if(tempPieceId == -4){
                bishopNumber++;
            }
        }
    }

    if(bishopNumber == 2){
        bishopNumber = 0;
        return 10;
    }
    else{
        return 0;
    }
}
