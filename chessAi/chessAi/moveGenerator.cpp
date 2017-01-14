// moveGenerator.cpp finds all legal moves of any piece on the board.
// getLegalMoves() returns a pointer of an array containing all legal moves.

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Functions from board.cpp
void boardInit();
void displayBoard();
void addPiece(int pieceType, int pieceLocation);
void removePiece(int pieceLocation);
bool piecePresent(int pieceLocation);
int getTopColor();
void newGameSetup(int top);

static int legalMovesArr[64];

// Functions that generate legal moves for each piece.
void pawnGen(int pieceLocation, int pieceType);

// Function that is called to find all legal moves of a specific piece.
int *getLegalMoves(int pieceType, int pieceLocation){

    // Fills array with -1 for viewing purposes.
    fill_n(legalMovesArr, 65,-1);

    int tempPieceId = abs(pieceType);

    switch(tempPieceId){
        case 1: pawnGen(pieceLocation, pieceType);

    }

    return legalMovesArr;
}

void pawnGen(int pieceLocation, int pieceType){
    // Legal moves of a pawn.
    // 1. One forward if nothing is in way.
    // 2. Two forward if on row 1 or 6.  Don't worry about overshooting, it will return as filled.
    // 3. En passant. ???
    // 4. Turn into something else if on row 0 or 7.

    // Starting position of array of legal moves.
    int currArrPos = 0;

    // Which color is on top of board.
    int topColor = getTopColor();

    // Piece is moving down.
    if((topColor == 0 && pieceType == 1) || (topColor == 1 && pieceType == -1)){

        // 1. One Forward if nothing is in it's way.
        if(piecePresent(pieceLocation + 8) == false){
            legalMovesArr[currArrPos] = (pieceLocation + 8);
            currArrPos++;
        }
    }
    // Piece is moving up.
    else{
         // 1. One Forward if nothing is in it's way.
        if(piecePresent(pieceLocation - 8) == false){
            legalMovesArr[currArrPos] = (pieceLocation - 8);
            currArrPos++;
        }
    }



}


