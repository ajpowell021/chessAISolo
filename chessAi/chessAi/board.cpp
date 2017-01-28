// board.cpp contains the logic for the board representation and nothing else.
// It only stores the board representation and contains the logic for moving
// pieces on the board.  No move logic is contained here.

#include <iostream>

using namespace std;

// Board declaration
int boardArray[8][8] = {};

// Variable defining which color is on top of screen.
// 0 if white.
// 1 if black.
int topColor;


// Initializes the board for new game.
void boardInit()
{

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            boardArray[i][j] = 0;
        }
    }
}

// Adds a piece to the board.
// pieceType is which piece to add, while
// pieceLocation is the square to add it to.
void addPiece(int pieceType, int pieceLocation){

    int xPos = (pieceLocation / 8);
    int yPos = (pieceLocation % 8);

    boardArray[xPos][yPos] = pieceType;
}

void removePiece(int pieceLocation){

    int xPos = (pieceLocation / 8);
    int yPos = (pieceLocation % 8);

    boardArray[xPos][yPos] = 0;
}

// Returns true if a piece is present,
// returns false if location is empty.
bool piecePresent(int pieceLocation){

    int xPos = (pieceLocation / 8);
    int yPos = (pieceLocation % 8);

    if(boardArray[xPos][yPos] != 0){
        return true;
    }
    else{
        return false;
    }
}

// Returns which type of piece is in a given square.
// Will return 0 if it's empty.
int getPieceType(int pieceLocation){

    int xPos = pieceLocation / 8;
    int yPos = pieceLocation % 8;
    int temp = boardArray[xPos][yPos];
    return temp;
}

// Destination is the square that the piece being captured is on,
// capture piece is the type of the piece doing the capturing.
// Returns true if pieces are different colors.
bool capturablePiece(int destination, int capturePiece){

    int defender = getPieceType(destination);

    if(capturePiece < 0 && defender > 0){
        return true;
    }
    else if(capturePiece > 0 && defender < 0){
        return true;
    }
    else{
        return false;
    }
}

// Displays the board to the console for viewing.
void displayBoard(){

    for(int i = 0; i < 8; i++){
            cout << endl;
        for(int j = 0; j < 8; j++){
                cout << boardArray[i][j] << "  ";
        }
    }
    cout << endl;
}

// Function defining which color is on top of screen.
// 0 if white.
// 1 if black.
int getTopColor(){

    return topColor;
}

// Places a piece in the needed locations for a new game.
void newGameSetup(int top){

    topColor = top;
    int pieceArrayNewGame[16] = {2, 3, 4, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1};

    if(topColor == 1){
        pieceArrayNewGame[3] = 5;
        pieceArrayNewGame[4] = 6;
        for(int i = 0; i < 16; i++){
            pieceArrayNewGame[i] *= -1;
        }
    }

    // Top Rows.
    for(int i = 0; i < 16; i++){
        addPiece(pieceArrayNewGame[i], i);
    }

    // Bottom Rows

    if(topColor == 0){
        pieceArrayNewGame[3] = 5;
        pieceArrayNewGame[4] = 6;
    }
    else{
        pieceArrayNewGame[3] = -6;
        pieceArrayNewGame[4] = -5;
    }

    for(int i = 0; i < 16; i++){
        pieceArrayNewGame[i] *= -1;
    }

    int j = 0;
    for(int i = 63; i > 47; i--){
        addPiece(pieceArrayNewGame[j], i);
        j++;
    }
}






