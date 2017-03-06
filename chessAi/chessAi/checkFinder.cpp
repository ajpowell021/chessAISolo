// checkFinder.cpp runs at the end of every move in order to see
// if either king is currently in check.

#include <iostream>

using namespace std;

// Is white in check right now?
bool whiteInCheck = false;

// Is black in check right now?
bool blackInCheck = false;

// Functions from board.cpp
int getPieceType(int pieceLocation);

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

    cout << "location: " << location << endl;

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

bool getWhiteCheck(){
    return whiteInCheck;
}

bool getBlackCheck(){
    return blackInCheck;
}
