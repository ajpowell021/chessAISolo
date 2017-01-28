// main.cpp controls all other .cpp files in the program.
// It tells every other file when to run and what to run.

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

// Functions from threatChecker.cpp
void displayAttackBoard(int color);
void buildWhiteAttackBoard();
void buildBlackAttackBoard();

int main(){

    boardInit();
    // 0 meaning white is on top, 1 meaning black is on top.
    newGameSetup(1);
    removePiece(59);
    addPiece(5, 35);
    displayBoard();


    int *legalMovesArr;
    legalMovesArr = getLegalMoves(6, 37);

    // Displays all legal moves for a specific piece.
    cout << endl << "legal squares to move to: " << endl;
    for(int i = 0; i < 64; i++){
            if((*(legalMovesArr + i)) > -1){
                cout << *(legalMovesArr + i) << endl;
            }
    }

    buildBlackAttackBoard();
    displayAttackBoard(1);

    return 0;
}
