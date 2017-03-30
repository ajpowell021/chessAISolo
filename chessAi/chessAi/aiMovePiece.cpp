
#include <iostream>

using namespace std;

// Functions from other files.
int getPieceType(int location);
int getTurn();
int *getLegalMoves(int pieceType, int pieceLocation);
int getTopColor();
bool checkThreat(int tempPiece, int location);
bool moveEndsInCheck(int origin, int destination, int color);
int getPassantLocation();
int pawnPromotionCheck();
void addPiece(int pieceType, int pieceLocation);
void removePiece(int pieceLocation);
void moveRookCastle(int destination);

// Functions in this file.
void fillAiLegalMoves(int pieceType, int pieceLocation);
void checkAiCastle(int pieceType, int pieceLocation);
void copyVariables();
void adjustAiRookBools(int pieceLocation, int pieceType);
void setWhiteAiCastle();
void setBlackAiCastle();
bool getWhiteAiCastle();
bool getBlackAiCastle();
void emptyMoveArray();
void addCastleToAiArray(int tempPiece);

// Gloabl Variables
int legalAiMoves[64];

// Castle Variables
bool topLeftAiCastle = false;
bool topRightAiCastle = false;
bool botLeftAiCastle = false;
bool botRightAiCastle = false;

// Have the rooks moved?
bool topLeftAiRook = false;
bool topRightAiRook = false;
bool botLeftAiRook = false;
bool botRightAiRook = false;

// Check Finder Values
bool whiteAiInCheck = false;
bool blackAiInCheck = false;

// Has a castle occured.
bool whiteAiHasCastled = false;
bool blackAiHasCastled = false;
bool castleHappenedThisTurn = false;

// Functions for getting these
// variables.
bool getTopLeftCastle();
bool getTopRightCastle();
bool getBotLeftCastle();
bool getBotRightCastle();
bool getTopLeftRook();
bool getTopRightRook();
bool getBotLeftRook();
bool getBotRightRook();
bool getWhiteCheck();
bool getBlackCheck();
bool getWhiteCastle();
bool getBlackCastle();

// Performs a move for the ai.  Very similar to the
// movePiece in main.cpp, but made for ai instead
// of human.
void aiMovePiece(int origin, int destination){

    copyVariables();
    emptyMoveArray();

    int pieceId = getPieceType(origin);
    int capturedPiece = getPieceType(destination);
    bool moveIsLegal = true;
    int turn = getTurn();
    bool moveIsCastle = false;

    fillAiLegalMoves(pieceId, origin);
    checkAiCastle(pieceId, origin);

    if (pieceId == 6 || pieceId == -6) {
        addCastleToAiArray(pieceId);
    }

    // Build Array
    for(int i = 0; i < 64; i++){
            if(legalAiMoves[i] > -1){
                if(legalAiMoves[i] == destination){
                    moveIsLegal = true;
                    i = 64;
                }
            }
        }

    // King Can't move into threat.
    if (pieceId == 6 || pieceId == -6) {
        if( checkThreat(pieceId, destination) == true) {
            moveIsLegal = false;
        }
    }

    // If player is in check, move can't leave them
    // still in check.
    if (turn == 0){
        if (getWhiteCheck() == true) {
            if (moveEndsInCheck(origin, destination, turn) == true) {
                moveIsLegal = false;
            }
        }
    }
    else{
        if (getBlackCheck() == true) {
            if (moveEndsInCheck(origin, destination, turn) == true) {
                moveIsLegal = false;
            }
        }
    }

    if (moveIsLegal == true) {

        // If a king or a rook is moving, the rook bools need
        // to be adjusted.
        if (pieceId == 6 || pieceId == -6 || pieceId == 2 || pieceId == -2) {
            adjustAiRookBools(origin, pieceId);
        }

        // If the move was a castle, the rook needs to be moved as well.
        if (pieceId == 6 || pieceId == -6) {
            if( (origin == 3 && destination == 1) || (origin == 3 && destination == 5) || (origin == 4 && destination == 2) || (origin == 4 && destination == 6) ||
            (origin == 59 && destination == 61) || (origin == 59 && destination == 57) || (origin == 60 && destination == 58) || (origin == 60 && destination == 62)) {
                castleHappenedThisTurn = true;
                moveRookCastle(destination);
                moveIsCastle = true;
                if (pieceId == 6){
                    setWhiteAiCastle();
                }
                if (pieceId == -6){
                    setBlackAiCastle();
                }
            }
        }

        removePiece(origin);
        addPiece(pieceId, destination);

        if (capturedPiece != 0){
            // Capture has occured!
        }

        // Handle en passant capture.
        if (pieceId == 1 || pieceId == -1) {
            if((origin - destination == 9) || (origin - destination == 7) || (origin - destination == -9) || (origin - destination == -7)){
                if (capturedPiece == 0){
                    // Move was diagonal without a capture, therefor a passant.
                    int temp = getPassantLocation();
                    removePiece(temp);
                }
            }
        }

        // Piece has now been moved.
        int promotedPawnLocale = pawnPromotionCheck();
        int pieceColor = getPieceType(promotedPawnLocale);
        if (promotedPawnLocale != 100) {
            removePiece(promotedPawnLocale);
            addPiece(promotedPawnLocale, 5 * pieceColor);
        }



    }
    else {
        // Move is not legal, need a way to tell the ai this, make move
        // worth a huge negative amount?
    }

    emptyMoveArray();

    // Revert rook move if it was a castle.
    if (moveIsCastle == true) {

        if (destination == 1) {
            if (getPieceType(2) == 2) {
                removePiece(2);
                addPiece(2, 0);
            }
            else if (getPieceType(2) == -2){
                removePiece(2);
                addPiece(-2, 0);
            }
        }

        if (destination == 2) {
            if (getPieceType(3) == 2) {
                removePiece(3);
                addPiece(2, 0);
            }
            else if (getPieceType(3) == -2) {
                removePiece(3);
                addPiece(-2, 0);
            }
        }

        if (destination == 5) {
            if (getPieceType(4) == 2) {
                removePiece(4);
                addPiece(2, 7);
            }
            else if (getPieceType(4) == -2) {
                removePiece(4);
                addPiece(-2,7);
            }
        }

        if (destination == 6) {
            if (getPieceType(5) == 2) {
                removePiece(5);
                addPiece(2, 7);
            }
            else if (getPieceType(5) == -2) {
                removePiece(5);
                addPiece(-2, 7);
            }
        }

        if (destination == 58){
            if (getPieceType(59) == 2) {
                removePiece(59);
                addPiece(2, 56);
            }
            else if (getPieceType(59) == -2) {
                removePiece(59);
                addPiece(-2, 56);
            }
        }

        if (destination == 57) {
            if (getPieceType(58) == 2) {
                removePiece(58);
                addPiece(2, 56);
            }
            else if (getPieceType(58) == -2) {
                removePiece(58);
                addPiece(-2, 56);
            }
        }

        if (destination == 62) {
            if (getPieceType(61) == 2) {
                removePiece(61);
                addPiece(2, 63);
            }
            else if (getPieceType(61) == -2) {
                removePiece(61);
                addPiece(-2, 63);
            }
        }

        if(destination == 61) {
            if (getPieceType(60) == 2) {
                removePiece(60);
                addPiece(2, 63);
            }
            else if (getPieceType(60) == -2) {
                removePiece(60);
                addPiece(-2, 63);
            }
        }
    }
}

void emptyMoveArray() {
    fill_n(legalAiMoves, 65, -1);
}

// Adds castle to the move array if
// the move is legal.
void addCastleToAiArray(int tempPiece){
    int topColor = getTopColor();
      if(tempPiece == 6){
          if(topColor == 0){
            if(topLeftAiCastle == true){
                legalAiMoves[10] = 1;
            }
            if(topRightAiCastle == true){
                legalAiMoves[11] = 5;
            }
          }
          else{
              if(botLeftAiCastle == true){
                  legalAiMoves[10] = 58;
              }
              if(botRightAiCastle == true){
                  legalAiMoves[11] = 62;
              }
          }
      }
      else{
          if(topColor == 1){
              if(topLeftAiCastle == true){
                  legalAiMoves[10] = 2;
              }
              if(topRightAiCastle == true){
                 legalAiMoves[11] = 6;
              }
          }
          else{
              if(botLeftAiCastle == true){
                  legalAiMoves[10] = 57;
              }
              if(botRightAiCastle == true){
                  legalAiMoves[11] = 61;              }
          }
      }
}

void copyVariables() {
    topLeftAiCastle = getTopLeftCastle();
    topRightAiCastle = getTopRightCastle();
    botLeftAiCastle = getBotLeftCastle();
    botRightAiCastle = getBotRightCastle();
    topLeftAiRook = getTopLeftRook();
    topRightAiRook = getTopRightRook();
    botLeftAiRook = getBotLeftRook();
    botRightAiRook = getBotRightRook();
    blackAiInCheck = getBlackCheck();
    whiteAiInCheck = getWhiteCheck();
    whiteAiHasCastled = getWhiteCastle();
    blackAiHasCastled = getBlackAiCastle();
}

// Gets an array of legal moves for a specific
// piece.  Fills in array: legalMoves.
void fillAiLegalMoves(int pieceType, int pieceLocation){

    int *legalAiMovesArr;
    legalAiMovesArr = getLegalMoves(pieceType, pieceLocation);

    for(int i = 0; i < 64; i++){
        if((*(legalAiMovesArr + i)) > -1){
            legalAiMoves[i] = *(legalAiMovesArr + i);
        }
    }
}

// Checks to see if a castle is a
// legal move here or not.
void checkAiCastle(int pieceType, int pieceLocation){
    int topColor = getTopColor();

    // White-Top
    if(topColor == 0){
        if(topLeftAiRook == false){
            int temp = getPieceType(1) + getPieceType(2);
            if(temp == 0){
                if(checkThreat(6, 3) == false){
                    if(checkThreat(6, 2) == false){
                        if(checkThreat(6, 1) == false){
                            // King can castle to top left!
                            topLeftAiCastle = true;
                        }
                        else{
                            topLeftAiCastle = false;
                        }
                    }
                    else{
                        topLeftAiCastle = false;
                    }
                }
                else{
                    topLeftAiCastle = false;
                }
            }
            else{
                topLeftAiCastle = false;
            }
        }
        else{
            topLeftAiCastle = false;
        }
        if(botLeftAiRook == false){
            int temp = getPieceType(58) + getPieceType(57);
            if(temp == 0){
                if(checkThreat(-6, 67) == false){
                    if(checkThreat(-6, 59) == false){
                        if(checkThreat(-6, 58) == false){
                                // King can castle to top left!
                                botLeftAiCastle = true;
                        }
                        else{
                            botLeftAiCastle = false;
                        }
                    }
                    else{
                        botLeftAiCastle = false;
                    }
                }
                else{
                    botLeftAiCastle = false;
                }
            }
            else{
                botLeftAiCastle = false;
            }
        }
        else{
            botLeftAiCastle = false;
        }
        if(topRightAiRook == false){
            int temp = getPieceType(4) + getPieceType(5) + getPieceType(6);
            if(temp == 0){
                if(checkThreat(6, 3) == false){
                    if(checkThreat(6, 4) == false){
                        if(checkThreat(6, 5) == false){
                            // King can castle to top left!
                            topRightAiCastle = true;
                        }
                        else{
                            topRightAiCastle = false;
                        }
                    }
                    else{
                        topRightAiCastle = false;
                    }
                }
                else{
                    topRightAiCastle = false;
                }
            }
            else{
                topRightAiCastle = false;
            }
        }
        else{
            topRightAiCastle = false;
        }
        if(botRightAiRook == false){
            int temp = getPieceType(60) + getPieceType(61) + getPieceType(62);
            if(temp == 0){
                if(checkThreat(-6, 60) == false){
                    if(checkThreat(-6, 61) == false){
                        if(checkThreat(-6, 59) == false){
                            // King can castle to top left!
                            botRightAiCastle = true;
                        }
                        else{
                            botRightAiCastle = false;
                        }
                    }
                    else{
                        botRightAiCastle = false;
                    }
                }
                else{
                    botRightAiCastle = false;
                }
            }
            else{
                botRightAiCastle = false;
            }
        }
        else{
            botRightAiCastle = false;
        }
    }
    // White-Bot
    else if(topColor == 1){
        if(botLeftAiRook == false){
            int temp = getPieceType(59) + getPieceType(58) + getPieceType(57);
            if(temp == 0){
                if(checkThreat(6, 60) == false){
                    if(checkThreat(6, 59) == false){
                        if(checkThreat(6, 58) == false){
                                // King can castle to top left!
                                botLeftAiCastle = true;
                        }
                        else{
                            botLeftAiCastle = false;
                        }
                    }
                    else{
                        botLeftAiCastle = false;
                    }
                }
                else{
                    botLeftAiCastle = false;
                }
            }
            else{
                botLeftAiCastle = false;
            }
        }
        else{
            botLeftAiCastle = false;
        }
        if(topLeftAiRook == false){
            int temp = getPieceType(1) + getPieceType(2) + getPieceType(3);
            if(temp == 0){
                if(checkThreat(-6, 3) == false){
                    if(checkThreat(-6, 2) == false){
                        if(checkThreat(-6, 4) == false){
                            // King can castle to top left!
                            topLeftAiCastle = true;
                        }
                        else{
                            topLeftAiCastle = false;
                        }
                    }
                    else{
                        topLeftAiCastle = false;
                    }
                }
                else{
                    topLeftAiCastle = false;
                }
            }
            else{
                topLeftAiCastle = false;
            }
        }
        else{
            topLeftAiCastle = false;
        }
        if(botRightAiRook == false){
            int temp = getPieceType(61) + getPieceType(62);
            if(temp == 0){
                if(checkThreat(6, 60) == false){
                    if(checkThreat(6, 61) == false){
                        if(checkThreat(6, 62) == false){
                            // King can castle to top left!
                            botRightAiCastle = true;
                        }
                        else{
                            botRightAiCastle = false;
                        }
                    }
                    else{
                        botRightAiCastle = false;
                    }
                }
                else{
                    botRightAiCastle = false;
                }
            }
            else{
                botRightAiCastle = false;
            }
        }
        else{
            botRightAiCastle = false;
        }
        if(topRightAiRook == false){
            int temp = getPieceType(5) + getPieceType(6);
            if(temp == 0){
                if(checkThreat(-6, 4) == false){
                    if(checkThreat(-6, 5) == false){
                        if(checkThreat(-6, 6) == false){
                            // King can castle to top left!
                            topRightAiCastle = true;
                        }
                        else{
                            topRightAiCastle = false;
                        }
                    }
                    else{
                        topRightAiCastle = false;
                    }
                }
                else{
                    topRightAiCastle = false;
                }
            }
            else{
                topRightAiCastle = false;
            }
        }
        else{
            topRightAiCastle = false;
        }
    }
}

void adjustAiRookBools(int pieceLocation, int pieceType) {

    if(pieceLocation == 0){
        topLeftAiRook = true;
        topLeftAiCastle = false;
    }
    else if(pieceLocation == 7){
        topRightAiRook = true;
        topRightAiCastle = false;
    }
    else if(pieceLocation == 56){
        botLeftAiRook = true;
        botLeftAiCastle = false;
    }
    else if(pieceLocation == 63){
        botRightAiRook = true;
        botRightAiCastle = false;
    }
    else if((pieceLocation == 3 && pieceType == 6) || pieceLocation == 4 && pieceType == -6){
        topLeftAiRook = true;
        topRightAiRook = true;
        topLeftAiCastle = false;
        topRightAiCastle = false;
    }
    else if((pieceLocation == 60 && pieceType == 6) || (pieceLocation == 59 && pieceType == -6)){
        botLeftAiRook = true;
        botRightAiRook = true;
        botLeftAiCastle = false;
        botRightAiCastle = false;
    }
}

void setWhiteAiCastle() {
    whiteAiHasCastled = true;
}

void setBlackAiCastle() {
    blackAiHasCastled = true;
}

bool getWhiteAiCastle() {
    return whiteAiHasCastled;
}

bool getBlackAiCastle() {
    return blackAiHasCastled;
}

bool getCastleHasHappenedThisTurn() {
    return castleHappenedThisTurn;
}

void resetCastleHasHappenedThisTurn() {
    castleHappenedThisTurn = false;
}
