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
void moveRookCastle(int destination);
void castleTestSetUp();
int pawnPromotionCheck();
void pawnPromotionSetUp();
void setWhiteCastle();
void setBlackCastle();
bool getWhiteCastle();
bool getBlackCastle();

// Functions from moveGenerator.cpp
int *getLegalMoves(int pieceType, int pieceLocation);
void pawnGen(int pieceLocation, int pieceType);
void rookGen(int pieceLocation, int pieceType);
void knightGen(int pieceLocation, int pieceType);
void bishopGen(int pieceLocation, int pieceType);
void queenGen(int pieceLocation, int pieceType);
void kingGen(int pieceLocation, int pieceType);
void makePassantTrue();
void makePassantFalse();
void setPassantLocation(int location);
int getPassantLocation();
int numMovesAvailable(int location);

// Functions from threatChecker.cpp
void displayAttackBoard(int color);
void buildWhiteAttackBoard();
void buildBlackAttackBoard();
bool checkThreat(int color, int location);
int getPiecesThatThreaten(int location);
int getPiecesThatProtect(int location);

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
void addCastleToArray(int tempPiece);
void numberMovesAvailable();

// Functions from boardScoreGen.cpp
int calcBoardScore(int color);

// Testing functions.
int generatePawnScore(int location, int color);
int generateKnightScore(int location, int color);
int generateBishopScore(int location, int color);
int generateRookScore(int location, int color);
int generateQueenScore(int location, int color);
int generateKingScore(int location, int color);

// From checkFinder.cpp
bool pieceInCheck(int color);
bool getWhiteCheck();
bool getBlackCheck();

// From mateSearcher.cpp
bool playerCanMove(int color);
bool moveEndsInCheck(int origin, int destination, int color);

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
    removePiece(52);
    removePiece(12);
    removePiece(3);
    addPiece(-1, 3);
    removePiece(5);
    addPiece(-1, 5);
    removePiece(6);
    //pawnPromotionSetUp();
    //castleTestSetUp();
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
        else if(command == "getMoves"){
            displayLegalMoves();
        }
        // These two are for testing.
        else if(command == "score"){
            cout << calcBoardScore(0) << endl;
        }
        else if(command == "pawn"){
            cout << generatePawnScore(52, 0);
        }
        else if(command == "knight"){
            cout << generateKnightScore(62, 0) << endl;
        }
        else if(command == "queen"){
            cout << generateQueenScore(60, 0) << endl;
        }
        else if(command == "king"){
            cout << generateKingScore(59, 0) << endl;
        }
        else if(command == "numMoves"){
            numberMovesAvailable();
        }
        else if(command == "check"){
            cout << pieceInCheck(0) << endl;
        }
        else{

        }
    }

    return 0;
}

void numberMovesAvailable(){
    int location;

    cout << "Please enter a location: ";
    cin >> location;
    cout << endl;

    cout << "That piece has " << numMovesAvailable(location) << " legal moves available." << endl;
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
    bool moveIsCastle = false;

    cout <<endl << "From: ";
    cin >> origin;
    cout << "To: ";
    cin >> destination;

    tempPiece = getPieceType(origin);
    // Check turn for legality.
    if((tempPiece > 0 && turn == 0) || (tempPiece < 0 && turn == 1)){

        // Creates array of legal moves the piece can take.
        fillLegalMoves(tempPiece, origin);
        checkCastle(tempPiece, origin);

        if(tempPiece == 6 || tempPiece == -6){
            addCastleToArray(tempPiece);
        }

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

        // If player is currently in check, make sure the next move
        // will not end with them still being in check.
        if(turn == 0){
            if(getWhiteCheck() == true){
                // White is in check right now.
                if(moveEndsInCheck(origin, destination, turn) == true){
                    moveIsLegal = false;
                }
            }
        }
        else{
            if(getBlackCheck() == true){
                // Black is in check right now.
                if(moveEndsInCheck(origin, destination, turn) == true){
                    moveIsLegal = false;
                }
            }
        }

        // Handle the move here.
        if(moveIsLegal == true){

            // For castling.
            if(tempPiece == 6 || tempPiece == -6 || tempPiece == 2 || tempPiece == -2){
                adjustRookBools(origin, tempPiece);
            }

            // Check if rook needs to be moved in event of
            // a castle.
            if(tempPiece == 6 || tempPiece == -6){
                if(origin == 3 || origin == 4 || origin == 59 || origin == 60){
                    if( destination == 1 || destination == 5 || destination == 58 || destination == 62 || destination == 2 || destination == 6 || destination == 57 || destination == 61){
                        moveRookCastle(destination);
                        moveIsCastle = true;
                        if(tempPiece == 6){
                            setWhiteCastle();
                        }
                        if(tempPiece == -6){
                            setBlackCastle();
                        }
                    }
                }
            }

            removePiece(origin);
            destPiece = getPieceType(destination);
            addPiece(tempPiece, destination);
            if(destPiece != 0){
                // A capture took place.
                cout << "Capture" << endl;
            }

            // Check for en passant capture.
            if(tempPiece == 1 || tempPiece == -1){
                if((origin - destination == 9) || (origin - destination == 7) || (origin - destination == -9) || (origin - destination == -7)){
                    // Move is diagonal
                    if(destPiece == 0){
                        // Diagonal move by pawn with no capture, must be en passant.
                        int temp = getPassantLocation();
                        removePiece(temp);
                        cout << "En passant capture!" << endl;
                    }
                }
            }

            cout << endl << "Piece has been moved." << endl;
            if(moveIsCastle == false){
                addMoveToHistory(tempPiece, origin, destination, destPiece);
                if(tempPiece == 1 || tempPiece == -1){
                    if(((origin - destination) == 16) || (origin - destination == -16)){
                        makePassantTrue();
                        setPassantLocation(destination);
                    }
                    else{
                        makePassantFalse();
                    }
                }
                else{
                    makePassantFalse();
                }
            }
            else{
                makePassantFalse();
                if(destination == 58 || destination == 61 || destination == 2 || destination == 5){
                    // Queen's side castle.
                    // Whites turn, start new line.
                    if(turn == 0){
                        turnNumber++;
                        string tempTurnNumber;
                        ostringstream Convert;
                        Convert << turnNumber;
                        tempTurnNumber = Convert.str();
                        history[turnNumber] = tempTurnNumber + ". " + "O-O-O" + " ";
                    }
                    // Blacks turn, add to old line.
                    else{
                        string temp = history[turnNumber];
                        history[turnNumber] = temp + "O-O-O";
                    }
                }
                else{
                    // King's side castle.
                    // Whites turn, start new line.
                    if(turn == 0){
                        turnNumber++;
                        string tempTurnNumber;
                        ostringstream Convert;
                        Convert << turnNumber;
                        tempTurnNumber = Convert.str();
                        history[turnNumber] = tempTurnNumber + ". " + "O-O" + " ";
                    }
                    // Blacks turn, add to old line.
                    else{
                        string temp = history[turnNumber];
                        history[turnNumber] = temp + "O-O";
                    }
                }
            }
            if(pieceInCheck(turn) == true && turn == 0){
                cout << "Black is in check!" << endl;
            }
            else if(pieceInCheck(turn) == true && turn == 1){
                cout << "White is in check!" << endl;
            }
            if(playerCanMove(turn) == false && pieceInCheck(turn) == true){
                // Current player wins the game.
                if(turn == 0){
                    cout << "White wins by checkmate!" << endl;
                }
                else{
                    cout << "Black wins by checkmate!" << endl;
                }
            }
            else if(playerCanMove(turn) == false && pieceInCheck(turn) == false){
                cout << "Stale-mate!!!" << endl;
            }
            nextTurn();
        }
        else{
            cout << "Move is not legal." << endl;
        }
    }
    else{
        cout << "It is not this players turn." << endl;
    }

    // Check for pawn promotion.
    int promotedPawnLocation = pawnPromotionCheck();
    string pieceInto;
    bool pieceEntered = false;
    if(promotedPawnLocation != 100){
        int pieceColor = getPieceType(promotedPawnLocation);
        while (pieceEntered == false){

            cout << "Please type the name of the piece you would like the pawn in " << promotedPawnLocation
            << " to be promoted into: ";
            cin >> pieceInto;
            cout << endl;

            if(pieceInto == "queen"){
                removePiece(promotedPawnLocation);
                addPiece((5 * pieceColor), promotedPawnLocation);
                pieceEntered = true;
            }
            else if(pieceInto == "rook"){
                removePiece(promotedPawnLocation);
                addPiece((2 * pieceColor), promotedPawnLocation);
                pieceEntered = true;
            }
            else if(pieceInto == "knight"){
                removePiece(promotedPawnLocation);
                addPiece((3 * pieceColor), promotedPawnLocation);
                pieceEntered = true;
            }
            else if(pieceInto == "bishop"){
                removePiece(promotedPawnLocation);
                addPiece((4 * pieceColor), promotedPawnLocation);
                pieceEntered = true;
            }
            else{
                cout << "Please enter a valid name. For example, queen." << endl;
            }
        }
    }
    else{
        // No promotion.
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
        cout << "blacks turn" << endl;
        turn++;
    }
    else if(turn == 1){
        cout << "whites turn" << endl;
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
                        else{
                            topLeftCastle = false;
                        }
                    }
                    else{
                        topLeftCastle = false;
                    }
                }
                else{
                    topLeftCastle = false;
                }
            }
            else{
                topLeftCastle = false;
            }
        }
        else{
            topLeftCastle = false;
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
                        else{
                            botLeftCastle = false;
                        }
                    }
                    else{
                        botLeftCastle = false;
                    }
                }
                else{
                    botLeftCastle = false;
                }
            }
            else{
                botLeftCastle = false;
            }
        }
        else{
            botLeftCastle = false;
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
                        else{
                            topRightCastle = false;
                        }
                    }
                    else{
                        topRightCastle = false;
                    }
                }
                else{
                    topRightCastle = false;
                }
            }
            else{
                topRightCastle = false;
            }
        }
        else{
            topRightCastle = false;
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
                        else{
                            botRightCastle = false;
                        }
                    }
                    else{
                        botRightCastle = false;
                    }
                }
                else{
                    botRightCastle = false;
                }
            }
            else{
                botRightCastle = false;
            }
        }
        else{
            botRightCastle = false;
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
                        else{
                            botLeftCastle = false;
                        }
                    }
                    else{
                        botLeftCastle = false;
                    }
                }
                else{
                    botLeftCastle = false;
                }
            }
            else{
                botLeftCastle = false;
            }
        }
        else{
            botLeftCastle = false;
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
                        else{
                            topLeftCastle = false;
                        }
                    }
                    else{
                        topLeftCastle = false;
                    }
                }
                else{
                    topLeftCastle = false;
                }
            }
            else{
                topLeftCastle = false;
            }
        }
        else{
            topLeftCastle = false;
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
                        else{
                            botRightCastle = false;
                        }
                    }
                    else{
                        botRightCastle = false;
                    }
                }
                else{
                    botRightCastle = false;
                }
            }
            else{
                botRightCastle = false;
            }
        }
        else{
            botRightCastle = false;
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
                        else{
                            topRightCastle = false;
                        }
                    }
                    else{
                        topRightCastle = false;
                    }
                }
                else{
                    topRightCastle = false;
                }
            }
            else{
                topRightCastle = false;
            }
        }
        else{
            topRightCastle = false;
        }
    }
}

// Adds castle to the move array if
// the move is legal.
void addCastleToArray(int tempPiece){
    int topColor = getTopColor();
      if(tempPiece == 6){
          if(topColor == 0){
            if(topLeftCastle == true){
                legalMoves[10] = 1;
            }
            if(topRightCastle == true){
                legalMoves[11] = 5;
            }
          }
          else{
              if(botLeftCastle == true){
                  legalMoves[10] = 58;
              }
              if(botRightCastle == true){
                  legalMoves[11] = 62;
              }
          }
      }
      else{
          if(topColor == 1){
              if(topLeftCastle == true){
                  legalMoves[10] = 2;
              }
              if(topRightCastle == true){
                 legalMoves[11] = 6;
              }
          }
          else{
              if(botLeftCastle == true){
                  legalMoves[10] = 57;
              }
              if(botRightCastle == true){
                  legalMoves[11] = 61;              }
          }
      }
}
