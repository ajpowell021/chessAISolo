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
int addPiece(int pieceType, int pieceLocation);
int removePiece(int pieceLocation);

// Functions from threatChecker.cpp
bool checkThreat(int tempPiece, int location);

// Functions from checkFinder.cpp
bool pieceInCheck(int color);

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
                        // This covers a king not being able to move into check.
                        if(tempPiece == -6){
                            if(checkThreat(tempPiece, (*(legalMovesArray + j))) == false){
                                return true;
                            }
                        }
                        else{
                            int origin = i;
                            int destination = j;
                            int capturedPiece = getPieceType(destination);
                            bool returnValue;

                            removePiece(origin);

                            if(capturedPiece != 0){
                                removePiece(destination);
                            }

                            addPiece(tempPiece, destination);

                            if(pieceInCheck(0) == true){
                                returnValue = false;
                            }
                            else{
                                returnValue = true;
                            }

                            removePiece(destination);
                            addPiece(tempPiece, origin);
                            addPiece(capturedPiece, destination);

                            return returnValue;
                        }
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

                        // This covers a king not being able to move into check.
                        if(tempPiece ==  6){
                            if(checkThreat(tempPiece, (*(legalMovesArray + j))) == false){
                                return true;
                            }
                        }
                        else{
                            int origin = i;
                            int destination = j;
                            int capturedPiece = getPieceType(destination);
                            bool returnValue;

                            removePiece(origin);

                            if(capturedPiece != 0){
                                removePiece(destination);
                            }

                            addPiece(tempPiece, destination);

                            if(pieceInCheck(1) == true){
                                returnValue = false;
                            }
                            else{
                                returnValue = true;
                            }

                            removePiece(destination);
                            addPiece(tempPiece, origin);
                            addPiece(capturedPiece, destination);

                            return returnValue;
                        }
                    }
                }
            }
        }
        cout << "No moves for black" << endl;
        return false;
    }

}
