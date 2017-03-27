// checkFinder.cpp runs at the end of every move in order to see
// if either king is currently in check.

#include <iostream>

using namespace std;

// Is white in check right now?
bool whiteInCheck = false;

// Is black in check right now?
bool blackInCheck = false;

// Functions to return these values.
bool getWhiteCheck();
bool getBlackCheck();

// Functions from board.cpp
int getPieceType(int pieceLocation);
void addPiece(int pieceType, int location);
void removePiece(int location);

// Function from threatChecker.cpp
bool checkThreat(int tempPiece, int location);

// Color is the color of the piece
// that just ended their turn.
// So we are checking the other color
// for check.  Returns true or false.
bool pieceInCheck(int color){

    int tempPiece;
    int location;

    if(color == 0){
        tempPiece = -6;
    }
    else{
        tempPiece = 6;
    }

    for( int i = 0; i < 64; i++){
        if(getPieceType(i) == tempPiece){
            location = i;
        }
    }

    bool inCheck = checkThreat(tempPiece, location);
    if(inCheck == true && color == 0){
        blackInCheck = true;
    }
    else if(inCheck == true && color == 1){
        whiteInCheck = true;
    }
    else if(inCheck == false && color == 0){
        blackInCheck = false;
    }
    else{
        whiteInCheck = false;
    }

    return inCheck;
}

// Calculates a move into the future to see if
// it ends with a piece still being in check.
bool moveEndsInCheck(int origin, int destination, int color){

    int tempPieceId = getPieceType(origin);
    int kingPiece;
    int kingPosition;
    // True if a capture takes place this turn.
    bool capture = false;
    int capturedPiece = getPieceType(destination);

    if(capturedPiece != 0){
        capture = true;
    }

    removePiece(origin);
    addPiece(tempPieceId, destination);

    if(color == 0){
        kingPiece = 6;
    }
    else{
        kingPiece = -6;
    }

    for( int i = 0; i < 64; i++){
        if(getPieceType(i) == kingPiece){
            kingPosition = i;
        }
    }

    if(checkThreat(kingPiece, kingPosition) == true){
        // Move ends with check, return true.
        removePiece(destination);
        addPiece(tempPieceId, origin);

        if(capture == true){
            addPiece(capturedPiece, destination);
        }

        return true;
    }
    else{
        // Piece is legal, return false.
        removePiece(destination);
        addPiece(tempPieceId, origin);

        if(capture == true){
            addPiece(capturedPiece, destination);
        }

        return false;
    }
}

bool getWhiteCheck(){
    return whiteInCheck;
}

bool getBlackCheck(){
    return blackInCheck;
}
