#include "queen.hpp"

Queen::Queen(PieceColor color): Piece(color,"Rook"){};

bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    // Check if the move is within the board boundaries
    if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8)
        return false;

    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);

    // Queen can move diagonally or straight (horizontally or vertically)
    if (rowDiff != colDiff && rowDiff != 0 && colDiff != 0) {
        return false;
    }
    // Check if there are any pieces blocking the path
    int rowStep, colStep;
    if (destRow > srcRow){
        rowStep = 1;
    } else if (destRow < srcRow){
        rowStep = -1;
    } else {
        rowStep = 0;
    }

    if (destCol > srcCol) {
        colStep = 1;
    } else if (destCol < srcCol) {
        colStep = -1;
    } else {
        colStep = 0;
    }
    
    int row = srcRow + rowStep;
    int col = srcCol + colStep;
    while (row != destRow || col != destCol) {
        if (board[row][col] != nullptr)
            return false;
        row += rowStep;
        col += colStep;
    }

    // Check if the destination square is empty or contains an opponent's piece
    const Piece* destPiece = board[destRow][destCol];
    if (destPiece == nullptr || destPiece->getColor() != color)
        return true;

    return false;
}