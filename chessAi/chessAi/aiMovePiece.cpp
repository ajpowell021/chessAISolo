
#include <iostream>

using namespace std;

// Functions from other files.
int getPieceType(int location);
int getTurn();
int *getLegalMoves(int pieceType, int pieceLocation);
int getTopColor();
bool checkThreat(int tempPiece, int location);

// Functions in this file.
void fillAiLegalMoves(int pieceType, int pieceLocation);
void checkAiCastle(int pieceType, int pieceLocation);

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

// Performs a move for the ai.  Very similar to the
// movePiece in main.cpp, but made for ai instead
// of human.
void aiMovePiece(int origin, int destination){

    int pieceId = getPieceType(origin);
    int capturedPiece = getPieceType(destination);

    int turn = getTurn();

    fillAiLegalMoves(pieceId, origin);


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
