// knightScoreGen.cpp tallies the score of a knight on a specific square, and returns that score
// as an int to a total board score.

#include <iostream>

using namespace std;

// Function declarations.
int hasSideCastled(int color);
int getRookPositionScore(int location, int color);
int getRookDefendedValue(int location);
int getRookAttackedValue(int location);

// Functions from board.cpp
int getTopColor();
bool getWhiteCastle();
bool getBlackCastle();
bool getWhiteAiCastle();
bool getBlackAiCastle();
bool getEndGame();

// Functions from threatChecker.cpp
int getPiecesThatProtect(int location);
int getPiecesThatThreaten(int location);

// Main function that is called by the
// board score generator.  Location is
// the square number of the piece.
// Color is the color of the rook that is
// in the square.
int generateRookScore(int location, int color){

    int score = 0;
    int rookScore = 500;

    score += rookScore;
    score += getRookDefendedValue(location);
    score -= getRookAttackedValue(location);
    score += hasSideCastled(color);

    return score;
}

// Checks to see if the the rook's side has
// completed a castle yet or not.
int hasSideCastled(int color){

    if(color == 0){
        if(getWhiteCastle() == false){
            return 10;
        }
        else{
            return 0;
        }
    }
    else{
        if(getBlackCastle() == false){
            return 10;
        }
        else{
            return 0;
        }
    }
}

int getRookDefendedValue(int location){

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
int getRookAttackedValue(int location){

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
