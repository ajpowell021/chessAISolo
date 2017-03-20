
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Functions in this file.
void storeBoardInfo(int from, int to);
void beginTurn(int color);
void turnChecker(int location);
void addToArray(int move);
void addCastleToMoves(int pieceNumber);
int getPieceType();
int getCapturedPiece();
int getOrigin();
int getDestination();
void makeMove(int location, int arrayPos);
int findSizeOfMoveArray();
void displayScoreArray();

// Other functions that are needed.
int getPieceType(int pieceLocation);
int addPiece(int pieceType, int pieceLocation);
int removePiece(int pieceLocation);
int getTopColor();
bool getTopLeftCastle();
bool getTopRightCastle();
bool getBotLeftCastle();
bool getBotRightCastle();
int *getLegalMoves(int pieceType, int pieceLocation);
int calcBoardScore(int color);

// Storing current board position.
int origin;
int destination;
int pieceType;
int capturedPiece;
/////////////////////////////////

// Array holding moves for a piece.
int movesForPiece[40];
int arraySpot = 0;
int scoreArray[10000];
int scoreArraySpot = 0;

void storeBoardInfo(int from, int to) {
    pieceType = getPieceType(from);
    capturedPiece = getPieceType(to);
    origin = from;
    destination = to;
}

int getPieceType() {
    return pieceType;
}

int getCapturedPiece() {
    return capturedPiece;
}

int getOrigin() {
    return origin;
}

int getDestination() {
    return destination;
}

// Main contacts the ai, letting it
// know it is it's turn.
// AI finds a piece.
void beginTurn(int color) {

    fill_n(scoreArray, 10000, -999999);
    // First, we search for a piece of the same color.
    for (int i = 0; i < 64; i++) {
        if(color == 0){
            if (getPieceType(i) > 0) {
                // Found a white piece.
                turnChecker(i);
            }
        }
        else{
            if (getPieceType(i) < 0) {
                // Found a black piece.
                turnChecker(i);
            }

        }
    }
}

void turnChecker(int location) {

    int pieceNumber = getPieceType(location);

    // Find all available moves for that piece.
    int *pointerMovesForPiece;
    pointerMovesForPiece = getLegalMoves(pieceNumber, location);

    for (int i = 0; i < 64; i++) {
        if((*(pointerMovesForPiece + i)) > -1) {
            addToArray(*(pointerMovesForPiece + i));
        }
    }

    if(pieceNumber == 6 || pieceNumber == -6){
        addCastleToMoves(pieceNumber);
    }

    // movesForPiece should now contain every legal move for that piece.
    // still concerned with moving the rook on a castle? Need to handle that
    // logic here.

    // Carry out move.
    int arraySize = findSizeOfMoveArray();

    for (int i = 0; i < arraySize; i++) {
        cout << i << endl;
        makeMove(location, i);
    }
}

// Makes the move on the board, returns the score
// and then resets the board.
void makeMove(int location, int arrayPos) {
    int score = 0;
    storeBoardInfo(location, movesForPiece[arrayPos]);

    if(getCapturedPiece() != 0){
        removePiece(getDestination());
    }

    removePiece(getOrigin());
    addPiece(getPieceType(), getDestination());

    if(getPieceType() > 0){
        score = calcBoardScore(0);
    }
    else{
        score = calcBoardScore(1);
    }

    scoreArray[scoreArraySpot] = score;
    scoreArraySpot++;

    //SORTT THIS ALL OUT

    removePiece(getDestination());
    addPiece(getCapturedPiece(), getDestination());
    addPiece(getPieceType(), getOrigin());
    //cout << "1: " << scoreArray[0] << endl;
    //cout << "2: " << scoreArray[1] << endl;
    //cout << "3: " << scoreArray[2] << endl;
    //displayScoreArray();
}

void displayScoreArray(){

    cout << "START OF PIECE" << endl;

    for (int i = 0; i < scoreArraySpot + 1; i++) {
        if(scoreArray[i] != -999999){
            cout << scoreArray[i] << endl;
        }
    }
    cout << "END OF PIECE" << endl;
}

void addToArray(int move) {
    movesForPiece[arraySpot] = move;
    arraySpot++;
}

int findSizeOfMoveArray(){
    int counter = 0;

    for (int i = 0; i < 41; i++) {
        if (movesForPiece[i] > -1) {
            counter++;
        }
    }

    return counter;
}

// If a castle is possible, add it to array here.
void addCastleToMoves(int pieceNumber) {
    int top = getTopColor();

    if(pieceNumber > 0){
        // Find if white can castle.
        if (top == 0) {
            // White is on top
            if (getTopLeftCastle() == true) {
                addToArray(1);
            }
            if (getTopRightCastle() == true) {
                addToArray(5);
            }
        }
        else{
            // White is on bottom.
            if(getBotLeftCastle() == true){
                addToArray(58);
            }
            if(getBotRightCastle() == true){
                addToArray(62);
            }
        }
    }
    else{
        // Find if black can castle
        if ( top == 1){
            // Black is on top.
            if (getTopLeftCastle() == true) {
                addToArray(2);
            }
            if (getTopRightCastle() == true) {
                addToArray(6);
            }
        }
        else{
            // Black is on bottom
            if(getBotLeftCastle() == true){
                addToArray(57);
            }
            if(getBotRightCastle() == true){
                addToArray(61);
            }
        }
    }
}
