#include "Bishop.hpp"

Bishop::Bishop(PieceColor color): Piece(color,"Bishop"){};

bool Bishop::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
        return false;
    }
    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);

    //To check bishop has moved diagonally 
    if (rowDiff != colDiff) {
        return false;
    }

    //Check if any piece is blocking the path

    int rowStep, colStep;
    if(destRow > srcRow) {
        rowStep = 1;
    } else {
        rowStep = -1;
    }

    if(destCol > srcCol) {
        colStep = 1;
    } else {
        colStep = -1;
    }

    int row = srcRow + rowStep;
    int col = srcCol + colStep;

    while(row != destRow && col!= destCol) {
        if(board[row][col] != nullptr) {
            return false;
        }
        row += rowStep;
        col+= colStep;
    }
    const Piece* destPiece = board[destRow][destCol];
    if (destPiece == nullptr || destPiece->getColor() != color) {
        return true;
    }
    return false;

}