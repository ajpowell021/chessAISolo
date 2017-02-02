// threatChecker.cpp checks any single square on the board,
// and returns if it is being threatened by the other player
// or not.  It also creates two boards, one for each player,
// that show which squares are currently being attacked.

#include <iostream>

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

// Functions from moveGenerator.cpp
int *getLegalMoves(int pieceType, int pieceLocation);
int *getThreatenedSquares(int pieceType, int pieceLocation);
void pawnGen(int pieceLocation, int pieceType);
void rookGen(int pieceLocation, int pieceType);
void knightGen(int pieceLocation, int pieceType);
void bishopGen(int pieceLocation, int pieceType);
void queenGen(int pieceLocation, int pieceType);
void kingGen(int pieceLocation, int pieceType);
void pawnThreatGen(int pieceLocation, int pieceType);

// Functions from threatChecker.cpp


// The two attack boards.
int whiteAttackBoard[8][8] = {};
int blackAttackBoard[8][8] = {};

// Builds the white attack board.
void buildWhiteAttackBoard(){

    int tempPiece;
    int *legalMovesArr;
    int tempXPos;
    int tempYPos;

    for(int i = 0; i < 64; i++){
        tempPiece = getPieceType(i);
        if(tempPiece > 0){
            legalMovesArr = getThreatenedSquares(tempPiece, i);
            for(int j = 0; j < 64; j++){
                if((*(legalMovesArr + j)) > -1){
                    tempXPos = (*(legalMovesArr + j) / 8);
                    tempYPos = (*(legalMovesArr + j) % 8);
                    whiteAttackBoard[tempXPos][tempYPos] = 1;
                }
            }
        }
    }
}

// Builds the black attack board.
void buildBlackAttackBoard(){

    int tempPiece;
    int *legalMovesArr;
    int tempXPos;
    int tempYPos;

    for(int i = 0; i < 64; i++){
        tempPiece = getPieceType(i);
        if(tempPiece < 0){
            legalMovesArr = getThreatenedSquares(tempPiece, i);
            for(int j = 0; j < 64; j++){
                if((*(legalMovesArr + j)) > -1){
                    tempXPos = (*(legalMovesArr + j) / 8);
                    tempYPos = (*(legalMovesArr + j) % 8);
                    blackAttackBoard[tempXPos][tempYPos] = 1;
                }
            }
        }
    }
}

// Displays one of the color's attack boards.
// 0 for white, 1 for black.
void displayAttackBoard(int color){
    if(color == 0){
        buildWhiteAttackBoard();
        for(int i = 0; i < 8; i++){
            cout << endl;
            for(int j = 0; j < 8; j++){
                cout << whiteAttackBoard[i][j] << "  ";
            }
        }
        cout << endl;
    }
    else{
        buildBlackAttackBoard();
        for(int i = 0; i < 8; i++){
            cout << endl;
            for(int j = 0; j < 8; j++){
                cout << blackAttackBoard[i][j] << "  ";
            }
        }
        cout << endl;
    }
}

// Returns true if the location is threatened,
// color is 0 if threatened piece is white, 1
// if black.
bool checkThreat(int tempPiece, int location){
    int color;
    if(tempPiece > 0){
        color = 0;
    }
    else{
        color = 1;
    }
    if(color == 0){
        int row = location / 8;
        int col = location % 8;
        buildBlackAttackBoard();
        if(blackAttackBoard[row][col] != 0){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        int row = location / 8;
        int col = location % 8;
        buildWhiteAttackBoard();
        if(whiteAttackBoard[row][col] != 0){
            return true;
        }
        else{
            return false;
        }
    }
}
