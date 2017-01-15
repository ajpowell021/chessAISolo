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
int getPieceType(int pieceLocation);
bool capturablePiece(int destination, int capturePiece);

static int legalMovesArr[64];

// Which color is on top of board.
static int topColor;

// Functions that generate legal moves for each piece.
void pawnGen(int pieceLocation, int pieceType);
void rookGen(int pieceLocation, int pieceType);

// Function that is called to find all legal moves of a specific piece.
int *getLegalMoves(int pieceType, int pieceLocation){

    // Fills array with -1 for viewing purposes.
    fill_n(legalMovesArr, 65,-1);

    // Find out which color started game on top.
    topColor = getTopColor();

    int tempPieceId = abs(pieceType);

    switch(tempPieceId){
        case 1: pawnGen(pieceLocation, pieceType);
        case 2: rookGen(pieceLocation, pieceType);

    }

    return legalMovesArr;
}

void pawnGen(int pieceLocation, int pieceType){
    // Legal moves of a pawn.
    // 1. One forward if nothing is in way.
    // 2. Two forward if on row 1 or 6.
    // 3. Capture if possible.
    // 4. En passant. ???
    // 5. Turn into something else if on row 0 or 7.

    // Starting position of array of legal moves.
    int currArrPos = 0;

    // Piece is moving down.
    if((topColor == 0 && pieceType == 1) || (topColor == 1 && pieceType == -1)){

        // 1. One Forward if nothing is in it's way.
        if(piecePresent(pieceLocation + 8) == false){
            legalMovesArr[currArrPos] = (pieceLocation + 8);
            currArrPos++;

            // 2. Two Forward if nothing is in it's way.
            if(piecePresent(pieceLocation + 16) == false && pieceLocation / 8 == 1){
                legalMovesArr[currArrPos] = (pieceLocation + 16);
                currArrPos++;
            }
        }

        // 3. Capture if possible.
        if(piecePresent(pieceLocation + 9) == true && capturablePiece(pieceLocation + 9, pieceType) == true){
            legalMovesArr[currArrPos] = (pieceLocation + 9);
            currArrPos++;
        }
        if(piecePresent(pieceLocation + 7) == true && capturablePiece(pieceLocation + 7, pieceType) == true){
            legalMovesArr[currArrPos] = (pieceLocation + 7);
            currArrPos++;
        }

    }
    // Piece is moving up.
    else{
         // 1. One Forward if nothing is in it's way.
        if(piecePresent(pieceLocation - 8) == false){
            legalMovesArr[currArrPos] = (pieceLocation - 8);
            currArrPos++;

            // 2. Two Forward if nothing is in it's way.
            if(piecePresent(pieceLocation - 16) == false && pieceLocation / 8 == 6){
                legalMovesArr[currArrPos] = (pieceLocation - 16);
                currArrPos++;
            }
        }

        // 3. Capture if possible.
        if(piecePresent(pieceLocation - 9) == true && capturablePiece(pieceLocation - 9, pieceType) == true){
            legalMovesArr[currArrPos] = (pieceLocation - 9);
            currArrPos++;
        }
        if(piecePresent(pieceLocation - 7) == true && capturablePiece(pieceLocation - 7, pieceType) == true){
            legalMovesArr[currArrPos] = (pieceLocation - 7);
            currArrPos++;
        }
    }



}

void rookGen(int pieceLocation, int pieceType){

    // Legal moves of rook.
    // 1. Move up until edge of board or piece is hit.
    // 2. Move down until...
    // 3. Move left and right...
    // 4. Castling?

    // Starting position of array of legal moves.
    int currArrPos = 0;

    // 1. Moving up until edge of board or piece is hit.

    int distFromEdge = pieceLocation / 8;

    for(int i = 1; i < distFromEdge + 1; i++){
        if(piecePresent(pieceLocation - (8 * i)) == true){

            if(capturablePiece((pieceLocation - (8 * i)), pieceType) == true){
                legalMovesArr[currArrPos] = (pieceLocation - (8 * i));
                currArrPos++;
                i = (distFromEdge + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge + 1);
            }
        }
        else{
            legalMovesArr[currArrPos] = (pieceLocation - (8 * i));
            currArrPos++;
        }
    }

    // 2. Moving down...
    distFromEdge = 8 - distFromEdge;

    for(int i = 1; i < distFromEdge + 1; i++){
        if(piecePresent(pieceLocation + (8 * i)) == true){

            if(capturablePiece((pieceLocation + (8 * i)), pieceType) == true){
                legalMovesArr[currArrPos] = (pieceLocation + (8 * i));
                currArrPos++;
                i = (distFromEdge + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge + 1);
            }
        }
        else{
            legalMovesArr[currArrPos] = (pieceLocation + (8 * i));
            currArrPos++;
        }
    }

    // 3. Moving left
    distFromEdge = pieceLocation % 8;

    for(int i = 1; i < distFromEdge + 1; i++){
        if(piecePresent(pieceLocation - i) == true){

            if(capturablePiece((pieceLocation + (8 * i)), pieceType) == true){
                legalMovesArr[currArrPos] = (pieceLocation - i);
                currArrPos++;
                i = (distFromEdge + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge + 1);
            }
        }
        else{
            legalMovesArr[currArrPos] = (pieceLocation - i);
            currArrPos++;
        }
    }

    // 4. Moving Right
    distFromEdge = 8 - distFromEdge;

    for(int i = 1; i < distFromEdge; i++){
        if(piecePresent(pieceLocation + i) == true){

            if(capturablePiece((pieceLocation + (8 * i)), pieceType) == true){
                legalMovesArr[currArrPos] = (pieceLocation + i);
                currArrPos++;
                i = (distFromEdge);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge);
            }
        }
        else{
            legalMovesArr[currArrPos] = (pieceLocation + i);
            currArrPos++;
        }
    }
}

