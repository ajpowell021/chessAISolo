// main.cpp controls all other .cpp files in the program.
// It tells every other file when to run and what to run.

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>

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
string calculateCoordinates(int location);
void printHistory();
void nextTurn();


// Array of legal moves pulled from move generator.
int legalMoves[64];

// Move array for history, dynamic array of strings.
string history[300];
// Where in history array are we currently.
int turnNumber = 0;
// 0 is white, 1 is black.
int turn = 0;

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
        else if(command == "history"){
            printHistory();
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
    // Check turn for legality.
    if((tempPiece > 0 && turn == 0) || (tempPiece < 0 && turn == 1)){

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
            nextTurn();
        }
        else{
            cout << "Move is not legal." << endl;
        }
    }
    else{
        cout << "It is not this players turn." << endl;
    }
    emptyLegalMoves();
}

// Empties legal move array.
void emptyLegalMoves(){
    fill_n(legalMoves, 65,-1);
}

// Adds a move to the running history array.
// Array is kept in long algebraic notation.
void addMoveToHistory(int pieceType, int origin, int destination, int destPieceType){

    int tempPieceType = abs(pieceType);
    string one;
    string two;
    string three;
    string four;
    string total;

    // First part of history.
    // Originating piece.
    switch(tempPieceType){
        case 1:
            one = "";
            break;
        case 2:
            one = "R";
            break;
        case 3:
            one = "N";
            break;
        case 4:
            one = "B";
            break;
        case 5:
            one = "Q";
            break;
        case 6:
            one = "K";
            break;
    }

    // Second part of history.
    // The originating square.
    two = calculateCoordinates(origin);

    // Third part of history.
    // Capture or move.
    if(destPieceType == 0){
        three = "-";
    }
    else{
        three = "x";
    }

    // Fourth part of history.
    // Destination square.
    four = calculateCoordinates(destination);

    // Whole move together.
    total = one + two + three + four;

    // Whites turn, start new line.
    if(turn == 0){
        turnNumber++;
        string tempTurnNumber;
        ostringstream Convert;
        Convert << turnNumber;
        tempTurnNumber = Convert.str();
        history[turnNumber] = tempTurnNumber + ". " + total + " ";
    }
    // Blacks turn, add to old line.
    else{
        string temp = history[turnNumber];
        history[turnNumber] = temp + total;
    }
}

// Turns square number into common algebraic notation.
string calculateCoordinates(int location){
    string first;
    string second;
    string total;
    int row = location / 8;
    int col = location % 8;

    switch (col) {
        case 0:
            first = "a";
            break;
        case 1:
            first = "b";
            break;
        case 2:
            first = "c";
            break;
        case 3:
            first = "d";
            break;
        case 4:
            first = "e";
            break;
        case 5:
            first = "f";
            break;
        case 6:
            first = "g";
            break;
        case 7:
            first = "h";
            break;
        }

        switch (row) {
            case 0:
                second = "8";
                break;
            case 1:
                second = "7";
                break;
            case 2:
                second = "6";
                break;
            case 3:
                second = "5";
                break;
            case 4:
                second = "4";
                break;
            case 5:
                second = "3";
                break;
            case 6:
                second = "2";
                break;
            case 7:
                second = "1";
                break;
            }

        total = first + second;
        return total;
}

void printHistory(){
    for(int i = 0; i < turnNumber + 1; i++){
        cout << history[i] << endl;
    }
}

void nextTurn(){
    if(turn == 0){
        turn++;
    }
    else if(turn == 1){
        turn--;
    }
    else{
        cout << endl << "TURN ERROR" << endl;
    }
}
