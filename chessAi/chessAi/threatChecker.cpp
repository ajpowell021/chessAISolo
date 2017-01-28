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

// Functions from moveGenerator.cpp
int *getLegalMoves(int pieceType, int pieceLocation);
void pawnGen(int pieceLocation, int pieceType);
void rookGen(int pieceLocation, int pieceType);
void knightGen(int pieceLocation, int pieceType);
void bishopGen(int pieceLocation, int pieceType);
void queenGen(int pieceLocation, int pieceType);
void kingGen(int pieceLocation, int pieceType);

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
            legalMovesArr = getLegalMoves(tempPiece, i);
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
            legalMovesArr = getLegalMoves(tempPiece, i);
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
        for(int i = 0; i < 8; i++){
            cout << endl;
            for(int j = 0; j < 8; j++){
                cout << whiteAttackBoard[i][j] << "  ";
            }
        }
        cout << endl;
    }
    else{
        for(int i = 0; i < 8; i++){
            cout << endl;
            for(int j = 0; j < 8; j++){
                cout << blackAttackBoard[i][j] << "  ";
            }
        }
        cout << endl;
    }
}
