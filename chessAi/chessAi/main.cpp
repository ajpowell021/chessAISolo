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
void kingTestSetUp();

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
bool checkThreat(int color, int location);

// Functions from main.cpp
void returnLegalMoves();
void movePiece();
void emptyLegalMoves();
void addMoveToHistory(int pieceType, int origin, int destination, int destPieceType);
string calculateCoordinates(int location);
void printHistory();
void nextTurn();
void displayLegalMoves();
void adjustRookBools(int pieceLocation, int pieceType);
void checkCastle(int pieceType, int pieceLocation);

// Array of legal moves pulled from move generator.
int legalMoves[64];

// Move array for history, dynamic array of strings.
string history[300];
// Where in history array are we currently.
int turnNumber = 0;
// 0 is white, 1 is black.
int turn = 0;

// Has the rooks moved?
bool topLeftRook = false;
bool topRightRook = false;
bool botLeftRook = false;
bool botRightRook = false;

// Final legality of castling.
bool topLeftCastle = false;
bool topRightCastle = false;
bool botLeftCastle = false;
bool botRightCastle = false;

int main(){
    string command = "";
    boardInit();
    emptyLegalMoves();
    // 0 meaning white is on top, 1 meaning black is on top.
    newGameSetup(1);
    removePiece(50);
    removePiece(57);
    removePiece(58);
    removePiece(5);
    removePiece(6);
    //kingTestSetUp();
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
        else if(command == "wthreat"){
            displayAttackBoard(0);
        }
        else if(command == "bthreat"){
            displayAttackBoard(1);
        }
        else if(command == "getMoves")
            displayLegalMoves();
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
}

// Displays all legal moves for a specific piece.
void displayLegalMoves(){
    int pieceLocation;
    int pieceType;
    cout << "Move Location: ";
    cin >> pieceLocation;
    cout << "Piece Type: ";
    cin >> pieceType;

    int *legalMovesArr;
    legalMovesArr = getLegalMoves(pieceType, pieceLocation);

    for(int i = 0; i < 64; i++){
        if((*(legalMovesArr + i)) > -1){
            legalMoves[i] = *(legalMovesArr + i);
        }
    }

    cout << endl << "legal squares to move to: " << endl;
    for(int i = 0; i < 64; i++){
        if((*(legalMovesArr + i)) > -1){
            cout << *(legalMovesArr + i) << endl;
        }
    }
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

        // Creates array of legal moves the piece can take.
        fillLegalMoves(tempPiece, origin);

        // The castle check, piece being moved must be the king.
        //if(tempPiece == 6 || tempPiece == -6){
            checkCastle(tempPiece, origin);
        //}

        // Check to see if destination is in this list!
        for(int i = 0; i < 64; i++){
            if(legalMoves[i] > -1){
                if(legalMoves[i] == destination){
                    moveIsLegal = true;
                    i = 64;
                }
            }
        }

        // If moving the king, checks to see if any squares are
        // threatened.
        if(tempPiece == 6 || tempPiece == -6){
            if(checkThreat(tempPiece, destination) == true){
                moveIsLegal = false;
            }
        }

        // Handle the move here.
        if(moveIsLegal == true){

            // For castling.
            if(tempPiece == 6 || tempPiece == -6 || tempPiece == 2 || tempPiece == -2){
                adjustRookBools(origin, tempPiece);
            }

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

    cout << "top left: " << topLeftCastle << endl;
    cout << "top right: " << topRightCastle << endl;
    cout << "bot left: " << botLeftCastle << endl;
    cout << "bot right: " << botRightCastle << endl;

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

// Adjusts the bool values
// involved with castling.
void adjustRookBools(int pieceLocation, int pieceType){

    if(pieceLocation == 0){
        topLeftRook = true;
        topLeftCastle = false;
    }
    else if(pieceLocation == 7){
        topRightRook = true;
        topRightCastle = false;
    }
    else if(pieceLocation == 56){
        botLeftRook = true;
        botLeftCastle = false;
    }
    else if(pieceLocation == 63){
        botRightRook = true;
        botRightCastle = false;
    }
    else if((pieceLocation == 3 && pieceType == 6) || pieceLocation == 4 && pieceType == -6){
        topLeftRook = true;
        topRightRook = true;
        topLeftCastle = false;
        topRightCastle = false;
    }
    else if((pieceLocation == 60 && pieceType == 6) || (pieceLocation == 59 && pieceType == -6)){
        botLeftRook = true;
        botRightRook = true;
        botLeftCastle = false;
        botRightCastle = false;
    }
}

// Checks to see if a castle is a
// legal move here or not.
void checkCastle(int pieceType, int pieceLocation){
    int topColor = getTopColor();

    // White-Top
    if(topColor == 0){
        if(topLeftRook == false){
            int temp = getPieceType(1) + getPieceType(2);
            if(temp == 0){
                if(checkThreat(6, 3) == false){
                    if(checkThreat(6, 2) == false){
                        if(checkThreat(6, 1) == false){
                            // King can castle to top left!
                            topLeftCastle = true;
                        }
                    }
                }
            }
        }
        if(botLeftRook == false){
            int temp = getPieceType(58) + getPieceType(57);
            if(temp == 0){
                if(checkThreat(-6, 67) == false){
                    if(checkThreat(-6, 59) == false){
                        if(checkThreat(-6, 58) == false){
                                // King can castle to top left!
                                botLeftCastle = true;
                        }
                    }
                }
            }
        }
        if(topRightRook == false){
            int temp = getPieceType(4) + getPieceType(5) + getPieceType(6);
            if(temp == 0){
                if(checkThreat(6, 3) == false){
                    if(checkThreat(6, 4) == false){
                        if(checkThreat(6, 5) == false){
                            // King can castle to top left!
                            topRightCastle = true;
                        }
                    }
                }
            }
        }
        if(botRightRook == false){
            int temp = getPieceType(60) + getPieceType(61) + getPieceType(62);
            if(temp == 0){
                if(checkThreat(-6, 60) == false){
                    if(checkThreat(-6, 61) == false){
                        if(checkThreat(-6, 59) == false){
                            // King can castle to top left!
                            botRightCastle = true;
                        }
                    }
                }
            }
        }
    }
    // White-Bot
    else if(topColor == 1){
        if(botLeftRook == false){
            int temp = getPieceType(59) + getPieceType(58) + getPieceType(57);
            if(temp == 0){
                if(checkThreat(6, 60) == false){
                    if(checkThreat(6, 59) == false){
                        if(checkThreat(6, 58) == false){
                                // King can castle to top left!
                                botLeftCastle = true;
                        }
                    }
                }
            }
        }
        if(topLeftRook == false){
            int temp = getPieceType(1) + getPieceType(2) + getPieceType(3);
            if(temp == 0){
                if(checkThreat(-6, 3) == false){
                    if(checkThreat(-6, 2) == false){
                        if(checkThreat(-6, 4) == false){
                            // King can castle to top left!
                            topLeftCastle = true;
                        }
                    }
                }
            }
        }
        if(botRightRook == false){
            int temp = getPieceType(61) + getPieceType(62);
            if(temp == 0){
                if(checkThreat(6, 60) == false){
                    if(checkThreat(6, 61) == false){
                        if(checkThreat(6, 62) == false){
                            // King can castle to top left!
                            botRightCastle = true;
                        }
                    }
                }
            }
        }
        if(topRightRook == false){
            int temp = getPieceType(5) + getPieceType(6);
            if(temp == 0){
                if(checkThreat(-6, 4) == false){
                    if(checkThreat(-6, 5) == false){
                        if(checkThreat(-6, 6) == false){
                            // King can castle to top left!
                            topRightCastle = true;
                        }
                    }
                }
            }
        }
    }
}
