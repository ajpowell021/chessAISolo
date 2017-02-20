// pawnScoreGen.cpp tallies the score of a pawn on a specific square, and returns that score
// as an int to a total board score.

#include <iostream>

using namespace std;

// Function declarations.
int getPositionScore(int location, int color);

// Functions from board.cpp
int getTopColor();

// Sets the top color.
int topColor = getTopColor();

// The main function that gets called by the
// board score generator.  Location is the
// square number of the piece.
int generatePawnScore(int location, int color){

    int score = 0;
    int pawnScore = 100;

    score += pawnScore;
    score += getPositionScore(location, color);

    return score;
}

int getPositionScore(int location, int color){

    //int scoreTable[8][8] = {0};
    if(color == topColor){
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
        //for(int i = 0; i < 8; i++){
          //  for(int j = 0; j < 8; j++){
            //    scoreTable[i][j] = updatedScoreTable][i][j];
              //}
        //}
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
