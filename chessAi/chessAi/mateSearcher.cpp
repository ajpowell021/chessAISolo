// mateSearcher.cpp only fires when a king is put into check
// or there are no legal moves available for a player to make.
// It searches every available move for every single piece.
// If there are none, a checkmate or stale-mate has happened.

#include <iostream>

using namespace std;

// Functions from moveGenerator.cpp
int *getLegalMoves(int pieceType, int pieceLocation);

// Functions from checkFinder.cpp
bool getWhiteCheck();
bool getBlackCheck();

// Functions from board.cpp
int getPieceType(int location);

// Returns true if a player has at least on legal
// move left to make.
bool playerCanMove(int color){

    int *legalMovesArray;
    int tempPiece;

    if( color == 0 ){
        // Whites turn, checking to see if black can move.
        for(int i = 0; i < 64; i++){
            tempPiece = getPieceType(i);
            if(tempPiece < 0){
                legalMovesArray = getLegalMoves(tempPiece, i);
                for(int j = 0; j < 64; j++){
                    if((*(legalMovesArray + j)) > -1){
                        return true;
                    }
                }
            }
        }
        cout << "No moves for white" << endl;
        return false;
    }
    else{
        // Blacks turn, checking to see if white can move.
        for(int i = 0; i < 64; i++){
            tempPiece = getPieceType(i);
            if(tempPiece > 0){
                legalMovesArray = getLegalMoves(tempPiece, i);
                for(int j = 0; j < 64; j++){
                    if((*(legalMovesArray + j)) > -1){
                        return true;
                    }
                }
            }
        }
        cout << "No moves for black" << endl;
        return false;
    }

}
