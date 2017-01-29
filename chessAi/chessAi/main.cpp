// main.cpp controls all other .cpp files in the program.
// It tells every other file when to run and what to run.

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

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

// Functions from main.cpp
void returnLegalMoves();
void movePiece();
void emptyLegalMoves();
void addMoveToHistory(int pieceType, int origin, int destination, int destPieceType);

// Array of legal moves pulled from move generator.
int legalMoves[64];

// Move array for history, dynamic array of strings.
//vector<string> history;

int main(){
    string command = "";
    boardInit();
    emptyLegalMoves();
    // 0 meaning white is on top, 1 meaning black is on top.
    newGameSetup(1);

    // Get user input.
    while(command != "quit"){
        cin >> command;

        if(command == "move"){
            movePiece();
        }
        else if(command == "show"){
            displayBoard();
        }
    }

    return 0;
}

// Gets an array of legal moves for a specific
// piece.  Fills in array: legalMoves.
void fillLegalMoves(int pieceType, int pieceLocation){
    int *legalMovesArr;
    legalMovesArr = getLegalMoves(pieceType, pieceLocation);

    for(int i = 0; i < 64; i++){
        if((*(legalMovesArr + i)) > -1){
            legalMoves[i] = *(legalMovesArr + i);
        }
    }

    // Displays all legal moves for a specific piece.
    //cout << endl << "legal squares to move to: " << endl;
    //for(int i = 0; i < 64; i++){
        //if((*(legalMovesArr + i)) > -1){
        //    cout << *(legalMovesArr + i) << endl;
        //}
    //}
}

// Moves a piece from one square to another.
// Handles legality of move as well as capture.
void movePiece(){
    int origin;
    int destination;
    int tempPiece;
    int destPiece = 0;
    bool moveIsLegal = false;

    cout <<endl << "From: ";
    cin >> origin;
    cout << "To: ";
    cin >> destination;

    tempPiece = getPieceType(origin);
    fillLegalMoves(tempPiece, origin);

    // Check to see if destination is in this list!
    for(int i = 0; i < 64; i++){
        if(legalMoves[i] > -1){
            if(legalMoves[i] == destination){
                moveIsLegal = true;
                i = 64;
            }
        }
    }

    // Handle the move here, maybe history too.
    if(moveIsLegal == true){
        removePiece(origin);
        destPiece = getPieceType(destination);
        addPiece(tempPiece, destination);
        if(destPiece != 0){
            // A capture took place.
            cout << "Capture" << endl;
        }
        cout << endl << "Piece has been moved." << endl;
        addMoveToHistory(tempPiece, origin, destination, destPiece);
    }
    else{
        cout << "Move is not legal." << endl;
    }
    emptyLegalMoves();
}

// Empties legal move array.
void emptyLegalMoves(){
    fill_n(legalMoves, 65,-1);
}

// Adds a move to the running history array.
// Array is kept in Algebraic notation.
void addMoveToHistory(int pieceType, int origin, int destination, int destPieceType){
    // If destPieceType != 0, then there was a capture.
    cout << "here" << endl;
    //history.push_back("test1");
    //history.push_back("test2");

    //cout << history[0] << endl << history[1] << endl;
}
