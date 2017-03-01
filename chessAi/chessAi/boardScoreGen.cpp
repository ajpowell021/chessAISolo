// boardScoreGen.cpp calculates the score of an entire board by calling the different
// piece specific functions from different files and adding them all together.

#include <iostream>

using namespace std;

// Piece Functions
int generatePawnScore(int location, int color);
int generateKnightScore(int location, int color);
int generateRookScore(int location, int color);
int generateBishopScore(int location, int color);
int generateQueenScore(int location, int color);

// Board Functions
int getPieceType(int location);

// Calculates the board score,
// color = 0 if for white,
// color = 1 if for black.
int calcBoardScore(int color){

    int boardScore = 0;
    int colorModifier;
    int tempColor;

    if(color == 0){
        // For white board check.
        for(int i = 0; i < 64; i++){

            int tempPiece = getPieceType(i);
            // If statement is only here until function exists for all pieces...
            // Also, all the debugging trash...
            if(tempPiece < 6 && tempPiece > -6 ){
                switch (tempPiece){
                    case -1:
                        boardScore -= (generatePawnScore(i, 1));
                        cout << "black pawn: " << boardScore << endl;
                        break;
                    case 1:
                        boardScore += (generatePawnScore(i, 0));
                        cout << "white pawn: " << boardScore << endl;
                        break;
                    case -2:
                            boardScore -= (generateRookScore(i, 1));
                            cout << "black rook: " << boardScore << endl;
                            break;
                    case 2:
                        boardScore += (generateRookScore(i, 0));
                        cout << "white rook: " << boardScore << endl;
                        break;
                    case -3:
                        boardScore -= (generateKnightScore(i, 1));
                        cout << "black knight: " << boardScore<< endl;
                        break;
                    case 3:
                        boardScore += (generateKnightScore(i, 0));
                        cout << "white knight: " << boardScore << endl;
                        break;
                    case -4:
                        boardScore -= (generateBishopScore(i, 1));
                        break;
                    case 4:
                        boardScore += (generateBishopScore(i, 0));
                        break;
                    case -5:
                        boardScore -= (generateQueenScore(i, 1));
                        break;
                    case 5:
                        boardScore += (generateQueenScore(i, 0));
                        break;


                }
            }
        }
    }
    else{
        // For black board check.

    }

    return boardScore;
}
