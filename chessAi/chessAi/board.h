#ifndef BOARD_H
#define BOARD_H

void boardInit();
void displayBoard();
void addPiece(int pieceType, int pieceLocation);
void removePiece(int pieceLocation);
bool piecePresent(int pieceLocation);

#endif // BOARD_H
