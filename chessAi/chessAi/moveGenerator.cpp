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
void kingTestSetUp();

static int legalMovesArr[64];

int passantLocation;

// Which color is on top of board.
static int topColor;

// Functions that generate legal moves for each piece.
void pawnGen(int pieceLocation, int pieceType);
void rookGen(int pieceLocation, int pieceType);
void knightGen(int pieceLocation, int pieceType);
void bishopGen(int pieceLocation, int pieceType);
void queenGen(int pieceLocation, int pieceType);
void kingGen(int pieceLocation, int pieceType);

// Any extra functions for finding threatened
// squares.
void pawnThreatGen(int pieceLocation, int pieceType);

// Other Functions
bool inRange(int destination);
void makePassantTrue();
void makePassantFalse();
void setPassantLocation(int location);
int getPassantLocation();

// Variables
bool lastMovePassant = false;

// Function that returns only threatened squares.
// Called by threat checker, mostly for pawns.
int *getThreatenedSquares(int pieceType, int pieceLocation){

    // Fills array with -1 for viewing purposes.
    fill_n(legalMovesArr, 65,-1);

    // Find out which color started game on top.
    topColor = getTopColor();

    int tempPieceId = abs(pieceType);
    switch(tempPieceId){
        case 1: pawnThreatGen(pieceLocation, pieceType);
            break;
        case 2: rookGen(pieceLocation, pieceType);
           break;
        case 3: knightGen(pieceLocation, pieceType);
           break;
        case 4: bishopGen(pieceLocation, pieceType);
           break;
        case 5: queenGen(pieceLocation, pieceType);
           break;
        case 6: kingGen(pieceLocation, pieceType);
            break;
    }

    return legalMovesArr;
}

// Only diagonal captures are added.
void pawnThreatGen(int pieceLocation, int pieceType){

    // Starting position of array of legal moves.
    int currArrPos = 0;

    int col = pieceLocation % 8;

    // Piece is moving down.
    if((topColor == 0 && pieceType == 1) || (topColor == 1 && pieceType == -1)){

        // Capture if possible.
        if(col != 7){
            if(inRange(pieceLocation + 9) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 9);
                currArrPos++;
            }
        }

        if(col != 0){
            if(inRange(pieceLocation + 7) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 7);
                currArrPos++;
            }
        }
    }
    // Piece is moving up.

    else{
        // Capture if possible.
        if(col != 0){
            if(inRange(pieceLocation - 9) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 9);
                currArrPos++;
            }
        }
        if(col != 7){
            if(inRange(pieceLocation - 7) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 7);
                currArrPos++;
            }
        }
    }
}

// Function that is called to find all legal moves of a specific piece.
int *getLegalMoves(int pieceType, int pieceLocation){

    // Fills array with -1 for viewing purposes.
    fill_n(legalMovesArr, 65,-1);

    // Find out which color started game on top.
    topColor = getTopColor();

    int tempPieceId = abs(pieceType);
    switch(tempPieceId){
        case 1: pawnGen(pieceLocation, pieceType);
            break;
        case 2: rookGen(pieceLocation, pieceType);
           break;
        case 3: knightGen(pieceLocation, pieceType);
           break;
        case 4: bishopGen(pieceLocation, pieceType);
           break;
        case 5: queenGen(pieceLocation, pieceType);
           break;
        case 6: kingGen(pieceLocation, pieceType);
            break;
    }

    return legalMovesArr;
}

// Returns true if a legal move,
// false otherwise.
bool inRange(int destination){
    if(destination > -1 && destination < 64){
        return true;
    }
    else{
        return false;
    }
}

void pawnGen(int pieceLocation, int pieceType){
    // Legal moves of a pawn.
    // 1. One forward if nothing is in way.
    // 2. Two forward if on row 1 or 6.
    // 3. Capture if possible.
    // 4. En passant. ???
    // 5. Turn into something else if on 0 or 7.

    // Starting position of array of legal moves.
    int currArrPos = 0;

    // Which row is the pawn currently in.
    int row = pieceLocation / 8;

    // Piece is moving down.
    if((topColor == 0 && pieceType == 1) || (topColor == 1 && pieceType == -1)){

        // 1. One Forward if nothing is in it's way.
        if(piecePresent(pieceLocation + 8) == false){
            if(inRange(pieceLocation + 8) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 8);
                currArrPos++;
            }

            // 2. Two Forward if nothing is in it's way.
            if(piecePresent(pieceLocation + 16) == false && pieceLocation / 8 == 1){
                if(inRange(pieceLocation + 8) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + 16);
                    currArrPos++;
                }
            }
        }

        // 3. Capture if possible.
        if(piecePresent(pieceLocation + 9) == true && capturablePiece(pieceLocation + 9, pieceType) == true){
            if(inRange(pieceLocation + 9) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 9);
                currArrPos++;
            }
        }
        if(piecePresent(pieceLocation + 7) == true && capturablePiece(pieceLocation + 7, pieceType) == true){
            if(inRange(pieceLocation + 7) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 7);
                currArrPos++;
            }
        }

    }
    // Piece is moving up.
    else{
         // 1. One Forward if nothing is in it's way.
        if(piecePresent(pieceLocation - 8) == false){
            if(inRange(pieceLocation - 8) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 8);
                currArrPos++;
            }

            // 2. Two Forward if nothing is in it's way.
            if(piecePresent(pieceLocation - 16) == false && pieceLocation / 8 == 6){
                if(inRange(pieceLocation - 16) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 16);
                    currArrPos++;
                }
            }
        }

        // 3. Capture if possible.
        if(piecePresent(pieceLocation - 9) == true && capturablePiece(pieceLocation - 9, pieceType) == true){
            if(inRange(pieceLocation - 9) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 9);
                currArrPos++;
            }
        }
        if(piecePresent(pieceLocation - 7) == true && capturablePiece(pieceLocation - 7, pieceType) == true){
            if(inRange(pieceLocation - 7) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 7);
                currArrPos++;
            }
        }
    }

    // En passant
    // 1. Pawn must be 3 squares above starting position.
    // 2. Other pawn just moved two squares last turn and must be directly beside the pawn.
    // 3. The 2-square move must have happened on the last turn.
    if(pieceType == 1 && topColor == 1){
        // Piece is white, started on bottom.
        if(row == 3){
            if(lastMovePassant == true){
                if(passantLocation == (pieceLocation - 1)){
                    legalMovesArr[currArrPos] = (pieceLocation - 9);
                    currArrPos++;
                }
                else if(passantLocation == (pieceLocation + 1)){
                    legalMovesArr[currArrPos] = (pieceLocation - 7);
                    currArrPos++;
                }
                else{
                    // Left blank as no en passant is possible.
                }
            }
        }
    }
    else if(pieceType == 1 && topColor == 0){
        // Piece is white, started on top.
        if(row == 4){
            if(lastMovePassant == true){
                if(passantLocation == (pieceLocation - 1)){
                    legalMovesArr[currArrPos] = (pieceLocation + 7);
                    currArrPos++;
                }
                else if(passantLocation == (pieceLocation + 1)){
                    legalMovesArr[currArrPos] = (pieceLocation + 9);
                    currArrPos++;
                }
                else{
                    // Left blank as no en passant is possible.
                }
            }
        }
    }
    else if(pieceType == -1 && topColor == 1){
        // Piece is black, started on top.
        if(row == 4){
            if(lastMovePassant == true){
                if(passantLocation == (pieceLocation - 1)){
                    legalMovesArr[currArrPos] = (pieceLocation + 7);
                    currArrPos++;
                }
                else if(passantLocation == (pieceLocation + 1)){
                    legalMovesArr[currArrPos] = (pieceLocation + 9);
                    currArrPos++;
                }
                else{
                    // Left blank as no en passant is possible.
                }
            }
        }
    }
    else if(pieceType == -1 && topColor == 0){
        // Piece is black, started on bottom.
        if(row == 3){
            if(lastMovePassant == true){
                if(passantLocation == (pieceLocation - 1)){
                    legalMovesArr[currArrPos] = (pieceLocation - 9);
                    currArrPos++;
                }
                else if(passantLocation == (pieceLocation + 1)){
                    legalMovesArr[currArrPos] = (pieceLocation - 7);
                    currArrPos++;
                }
                else{
                    // Left blank as no en passant is possible.
                }
            }
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
                if(inRange(pieceLocation - (8 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - (8 * i));
                    currArrPos++;
                }
                i = (distFromEdge + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge + 1);
            }
        }
        else{
            if(inRange(pieceLocation - (8 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation - (8 * i));
                currArrPos++;
            }
        }
    }

    // 2. Moving down...
    distFromEdge = 8 - distFromEdge;

    for(int i = 1; i < distFromEdge + 1; i++){
        if(piecePresent(pieceLocation + (8 * i)) == true){

            if(capturablePiece((pieceLocation + (8 * i)), pieceType) == true){
                if(inRange(pieceLocation + (8 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + (8 * i));
                    currArrPos++;
                }
                i = (distFromEdge + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge + 1);
            }
        }
        else{
            if(inRange(pieceLocation + (8 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation + (8 * i));
                currArrPos++;
            }
        }
    }

    // 3. Moving left
    distFromEdge = pieceLocation % 8;

    for(int i = 1; i < distFromEdge + 1; i++){
        if(piecePresent(pieceLocation - i) == true){
            if(capturablePiece((pieceLocation - i), pieceType) == true){
                if(inRange(pieceLocation - i) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - i);
                    currArrPos++;
                }
                i = (distFromEdge + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge + 1);
            }
        }
        else{
            if(inRange(pieceLocation - i) == true){
                legalMovesArr[currArrPos] = (pieceLocation - i);
                currArrPos++;
            }
        }
    }

    // 4. Moving Right
    distFromEdge = 8 - distFromEdge;

    for(int i = 1; i < distFromEdge; i++){
        if(piecePresent(pieceLocation + i) == true){

            if(capturablePiece((pieceLocation + i), pieceType) == true){
                if(inRange(pieceLocation + i) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + i);
                    currArrPos++;
                }
                i = (distFromEdge);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdge);
            }
        }
        else{
            if(inRange(pieceLocation + i) == true){
                legalMovesArr[currArrPos] = (pieceLocation + i);
                currArrPos++;
            }
        }
    }
}

void knightGen(int pieceLocation, int pieceType){

    // Legal moves of knight.
    //
    // 1. Left moves if legal.
    // 2. Right moves if legal.
    // 3. Up moves if legal.
    // 4. Down moves if legal.

    int row = pieceLocation / 8;
    int col = pieceLocation % 8;
    int currArrPos = 0;

    // 1. Left moves if legal.
    if(col != 0 && col != 1){
        // Left moves are legal.
        // Left up.
        if(piecePresent(pieceLocation - 10) == true){
            if(capturablePiece(pieceLocation - 10, pieceType) == true){
                if(inRange(pieceLocation - 10) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 10);
                    currArrPos++;
                }
            }
            else{
                // Cannot move here as there is already a piece of the same color present.
            }
        }
        else{
            // Square is empty.
            if(inRange(pieceLocation - 10) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 10);
                currArrPos++;
            }
        }
        // Left down.
        if(piecePresent(pieceLocation + 6) == true){
            if(capturablePiece(pieceLocation + 6, pieceType) == true){
                if(inRange(pieceLocation + 6) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + 6);
                    currArrPos++;
                }
            }
            else{
                // Cannot move here as there is already a piece of the same color present.
            }
        }
        else{
            // Square is empty.
            if(inRange(pieceLocation + 6) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 6);
                currArrPos++;
            }
        }
    }

    // 2. Right moves if legal.
    if(col != 6 && col != 7){
        // Right moves are legal.
        // Right up.
        if(piecePresent(pieceLocation + 10) == true){
            if(capturablePiece(pieceLocation + 10, pieceType) == true){
                if(inRange(pieceLocation + 10) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + 10);
                    currArrPos++;
                }
            }
            else{
                // Cannot move here as there is already a piece of the same color present.
            }
        }
        else{
            // Square is empty.
            if(inRange(pieceLocation + 10) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 10);
                currArrPos++;
            }
        }
        // Right down.
        if(piecePresent(pieceLocation - 6) == true){
            if(capturablePiece(pieceLocation - 6, pieceType) == true){
                if(inRange(pieceLocation - 6) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 6);
                    currArrPos++;
                }
            }
            else{
                // Cannot move here as there is already a piece of the same color present.
            }
        }
        else{
            // Square is empty.
            if(inRange(pieceLocation - 6) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 6);
                currArrPos++;
            }
        }
    }

    // 3. Up moves if legal.
    if(row != 0 && row != 1){
    // Up left.
            if(piecePresent(pieceLocation - 17) == true){
                if(capturablePiece(pieceLocation - 17, pieceType) == true){
                    if(inRange(pieceLocation - 17) == true){
                        legalMovesArr[currArrPos] = (pieceLocation - 17);
                        currArrPos++;
                    }
                }
                else{
                    // Cannot move here as there is already a piece of the same color present.
                }
            }
            else{
                // Square is empty.
                if(inRange(pieceLocation - 17) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 17);
                    currArrPos++;
                }
            }

            // Up right
            if(piecePresent(pieceLocation - 15) == true){
                if(capturablePiece(pieceLocation - 15, pieceType) == true){
                    if(inRange(pieceLocation - 15) == true){
                        legalMovesArr[currArrPos] = (pieceLocation -15);
                        currArrPos++;
                    }
                }
                else{
                    // Cannot move here as there is already a piece of the same color present.
                }
            }
            else{
                // Square is empty.
                if(inRange(pieceLocation - 15) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 15);
                    currArrPos++;
                }
            }
    }

    // 4. Down moves if legal.
    if(row != 6 && row != 7){
    // Down left.
            if(piecePresent(pieceLocation + 15) == true){
                if(capturablePiece(pieceLocation + 15, pieceType) == true){
                    if(inRange(pieceLocation + 15) == true){
                        legalMovesArr[currArrPos] = (pieceLocation + 15);
                        currArrPos++;
                    }
                }
                else{
                    // Cannot move here as there is already a piece of the same color present.
                }
            }
            else{
                // Square is empty.
                if(inRange(pieceLocation + 15) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + 15);
                    currArrPos++;
                }
            }

            // Down right
            if(piecePresent(pieceLocation + 17) == true){
                if(capturablePiece(pieceLocation + 17, pieceType) == true){
                    if(inRange(pieceLocation + 17) == true){
                        legalMovesArr[currArrPos] = (pieceLocation + 17);
                        currArrPos++;
                    }
                }
                else{
                    // Cannot move here as there is already a piece of the same color present.
                }
            }
            else{
                // Square is empty.
                if(inRange(pieceLocation + 17) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + 17);
                    currArrPos++;
                }
            }
    }


}

void bishopGen(int pieceLocation, int pieceType){

    // Legal moves of bishop.
    //
    // 1. Move diagonal up left.
    // 2. Move diagonal up right.
    // 3. Move diagonal down left.
    // 4. Move diagonal down right.

    int currArrPos = 0;
    int distFromEdgeLeft = pieceLocation % 8;
    int distFromEdgeTop = pieceLocation / 8;
    int distFromEdgeRight = 7 - distFromEdgeLeft;
    int distFromEdgeBot = 7 - distFromEdgeTop;

    // 1. Move diagonal up left.
    int tempDist;
    if(distFromEdgeLeft > distFromEdgeTop){
        tempDist = distFromEdgeTop;
    }
    else{
        tempDist = distFromEdgeLeft;
    }

    for(int i = 1; i < tempDist + 1; i++){
        if(piecePresent(pieceLocation - 9 * i) == false){
            if(inRange(pieceLocation - (9 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation - (9 * i));
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation - (9 * i), pieceType) == true){
                if(inRange(pieceLocation - (9 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - (9 * i));
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }

    // 2. Move diagonal up right.
    if(distFromEdgeRight > distFromEdgeTop){
        tempDist = distFromEdgeTop;
    }
    else{
        tempDist = distFromEdgeRight;
    }

    for(int i = 1; i < tempDist + 1; i++){
        if(piecePresent(pieceLocation - (7 * i)) == false){
            if(inRange(pieceLocation - (7 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation - (7 * i));
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation - 7 * i, pieceType) == true){
                if(inRange(pieceLocation - (7 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 7 * i);
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }

    // 3. Move down left.
    if(distFromEdgeLeft > distFromEdgeBot){
        tempDist = distFromEdgeBot;
    }
    else{
        tempDist = distFromEdgeLeft;
    }

    for(int i = 1; i < tempDist + 1; i++){
        if(piecePresent(pieceLocation + (7 * i)) == false){
            if(inRange(pieceLocation + (7 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation + (7 * i));
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation + (7 * i), pieceType) == true){
                if(inRange(pieceLocation + (7 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + (7 * i));
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }

    // 4. Move down right.
    if(distFromEdgeRight > distFromEdgeBot){
        tempDist = distFromEdgeBot;
    }
    else{
        tempDist = distFromEdgeRight;
    }

    for(int i = 1; i < tempDist + 1; i++){
        if(piecePresent(pieceLocation + (9 * i)) == false){
            if(inRange(pieceLocation + (9 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation + (9 * i));
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation + (9 * i), pieceType) == true){
                if(inRange(pieceLocation + (9 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + (9 * i));
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }
}

void queenGen(int pieceLocation, int pieceType){

    // Legal moves of queen.
    //
    // 1. Move diagonal up left.
    // 2. Move diagonal up right.
    // 3. Move diagonal down left.
    // 4. Move diagonal down right.
    // 5. Move up.
    // 6. Move down.
    // 7. Move left.
    // 8. Move right.

    int currArrPos = 0;
    int distFromEdgeLeft = pieceLocation % 8;
    int distFromEdgeTop = pieceLocation / 8;
    int distFromEdgeRight = 8 - distFromEdgeLeft;
    int distFromEdgeBot = 7 - distFromEdgeTop;

    // 1. Move diagonal up left.
    int tempDist;
    if(distFromEdgeLeft > distFromEdgeTop){
        tempDist = distFromEdgeTop;
    }
    else{
        tempDist = distFromEdgeLeft;
    }

    for(int i = 1; i < tempDist + 1; i++){
        if(piecePresent(pieceLocation - (9 * i)) == false){
            if(inRange(pieceLocation - (9 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation - (9 * i));
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation - 9 * i, pieceType) == true){
                if(inRange(pieceLocation - (9 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 9 * i);
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }

    // 2. Move diagonal up right.
    if(distFromEdgeRight > distFromEdgeTop){
        tempDist = distFromEdgeTop;
    }
    else{
        tempDist = distFromEdgeRight;
    }

    for(int i = 1; i < tempDist + 1; i++){
        if(piecePresent(pieceLocation - (7 * i)) == false){
            if(inRange(pieceLocation - (7 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 7 * i);
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation - (7 * i), pieceType) == true){
                if(inRange(pieceLocation - (7 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - (7 * i));
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }

    // 3. Move diagonal down left.
    if(distFromEdgeLeft > distFromEdgeBot){
        tempDist = distFromEdgeBot;
    }
    else{
        tempDist = distFromEdgeLeft;
    }

    for(int i = 1; i < tempDist + 1; i++){
        if(piecePresent(pieceLocation + (7 * i)) == false){
            if(inRange(pieceLocation + (7 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation + (7 * i));
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation + (7 * i), pieceType) == true){
                if(inRange(pieceLocation + (7 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + (7 * i));
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }

    // 4. Move diagonal down right.
    if(distFromEdgeRight > distFromEdgeBot){
        tempDist = distFromEdgeBot;
    }
    else{
        tempDist = distFromEdgeRight;
    }

    for(int i = 1; i < tempDist; i++){
        if(piecePresent(pieceLocation + (9 * i)) == false){
            if(inRange(pieceLocation + (9 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation + (9 * i));
                currArrPos++;
            }
        }
        else{
            // There is a piece there, can it be captured or not?
            if(capturablePiece(pieceLocation + (9 * i), pieceType) == true){
                if(inRange(pieceLocation + (9 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + (9 * i));
                    currArrPos++;
                    i = tempDist;
                }
            }
            else{
                i = tempDist;
            }
        }
    }

    // 5. Move up.
    for(int i = 1; i < distFromEdgeTop + 1; i++){
        if(piecePresent(pieceLocation - (8 * i)) == true){

            if(capturablePiece((pieceLocation - (8 * i)), pieceType) == true){
                if(inRange(pieceLocation - (8 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - (8 * i));
                    currArrPos++;
                }
                i = (distFromEdgeTop + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdgeTop + 1);
            }
        }
        else{
            if(inRange(pieceLocation - (8 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation - (8 * i));
                currArrPos++;
            }
        }
    }

    // 6. Move down.
    //distFromEdgeBot = 7 - distFromEdgeBot;

    for(int i = 1; i < distFromEdgeBot + 1; i++){
        cout << "why" << endl;
        if(piecePresent(pieceLocation + (8 * i)) == true){

            if(capturablePiece((pieceLocation + (8 * i)), pieceType) == true){
                if(inRange(pieceLocation + (8 * i)) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + (8 * i));
                    currArrPos++;
                }
                i = (distFromEdgeBot + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdgeBot + 1);
            }
        }
        else{
            if(inRange(pieceLocation + (8 * i)) == true){
                legalMovesArr[currArrPos] = (pieceLocation + (8 * i));
                currArrPos++;
            }
        }
    }

    // 7. Move left.
    for(int i = 1; i < distFromEdgeLeft + 1; i++){
        if(piecePresent(pieceLocation - i) == true){

            if(capturablePiece((pieceLocation - i), pieceType) == true){
                if(inRange(pieceLocation - i) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - i);
                    currArrPos++;
                }
                i = (distFromEdgeLeft + 1);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdgeLeft + 1);
            }
        }
        else{
            if(pieceLocation + (8 * i) > -1){
                if(inRange(pieceLocation - i) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - i);
                    currArrPos++;
                }
            }
        }
    }

    // 8. Move right.
    for(int i = 1; i < distFromEdgeRight; i++){
        if(piecePresent(pieceLocation + i) == true){

            if(capturablePiece((pieceLocation + i), pieceType) == true){
                if(inRange(pieceLocation + i)== true){
                    legalMovesArr[currArrPos] = (pieceLocation + i);
                    currArrPos++;
                }
                i = (distFromEdgeRight);
            }
            else{
                // Do nothing, piece is blocked by same color.
                i = (distFromEdgeRight);
            }
        }
        else{
            if(inRange(pieceLocation + i)== true){
                legalMovesArr[currArrPos] = (pieceLocation + i);
                currArrPos++;
            }
        }
    }
}

void kingGen(int pieceLocation, int pieceType){

    // Legal moves of King
    //
    // 1. One up.
    // 2. One down.
    // 3. One left.
    // 4. One right.
    // 5. Can't move to any of these if the square is threatened.

    int currArrPos = 0;

    // 1. One up.
    if((pieceLocation / 8) > 0){
        if(piecePresent(pieceLocation - 8) == false){
            if(inRange(pieceLocation - 8) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 8);
                currArrPos++;
            }
        }
        else{
            if(capturablePiece(pieceLocation - 8, pieceType) == true){
                if(inRange(pieceLocation - 8) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 8);
                    currArrPos++;
                }
            }
        }
    }

    // 2. One down.
    if((pieceLocation / 8) < 7){
        if(piecePresent(pieceLocation + 8) == false){
            if(inRange(pieceLocation + 8) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 8);
                currArrPos++;
            }
        }
        else{
            if(capturablePiece(pieceLocation + 8, pieceType) == true){
                if(inRange(pieceLocation + 8) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + 8);
                    currArrPos++;
                }
            }
        }
    }

    // 3. One left.
    if((pieceLocation % 8) > 0){
        if(piecePresent(pieceLocation - 1) == false){
            if(inRange(pieceLocation - 1) == true){
                legalMovesArr[currArrPos] = (pieceLocation - 1);
                currArrPos++;
            }
        }
        else{
            if(capturablePiece(pieceLocation - 1, pieceType) == true){
                if(inRange(pieceLocation - 1) == true){
                    legalMovesArr[currArrPos] = (pieceLocation - 1);
                    currArrPos++;
                }
            }
        }
    }

    // 4. One right.
    if((pieceLocation % 8) < 7){
        if(piecePresent(pieceLocation + 1) == false){
            if(inRange(pieceLocation + 1) == true){
                legalMovesArr[currArrPos] = (pieceLocation + 1);
                currArrPos++;
            }
        }
        else{
            if(capturablePiece(pieceLocation + 1, pieceType) == true){
                if(inRange(pieceLocation + 1) == true){
                    legalMovesArr[currArrPos] = (pieceLocation + 1);
                    currArrPos++;
                }
            }
        }
    }
}

// Last move made was a double move.
void makePassantTrue(){
    lastMovePassant = true;
}

// Last move made was not a double move.
void makePassantFalse(){
    lastMovePassant = false;
}

void setPassantLocation(int location){
    passantLocation = location;
}

int getPassantLocation(){
    return passantLocation;
}
