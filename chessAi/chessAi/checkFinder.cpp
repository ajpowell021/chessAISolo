// checkFinder.cpp runs at the end of every move in order to see
// if either king is currently in check.

#include <iostream>

using namespace std;

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

    return checkThreat(tempPiece, location);
}
