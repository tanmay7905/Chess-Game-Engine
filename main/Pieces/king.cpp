#include "king.hpp"

King::King(PieceColor color): Piece(color,"King"){};

bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    // Check if the destination square is within one square distance from the source square
    int rowDiff = destRow - srcRow;
    int colDiff = destCol - srcCol;

    if (rowDiff < -1 || rowDiff > 1 || colDiff < -1 || colDiff > 1) {
        return false;
    }

    // Check if the destination square is either empty or occupied by an opponent's piece
    if (board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() == getColor()) {
        return false;
    }

    // Check if the destination square is not under attack by any opponent's piece
    PieceColor opponentColor = (getColor() == WHITE) ? BLACK : WHITE;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece != nullptr && piece->getColor() == opponentColor) {
                if (piece->isValidMove(row, col, destRow, destCol, board)) {
                    return false;
                }
            }
        }
    }

    return true;
};