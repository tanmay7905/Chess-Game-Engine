#include "pawn.hpp"

Pawn::Pawn(PieceColor color): Piece(color,"Pawn"){};

bool Pawn::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    // To check that move is within the board
    if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
        return false;
    }

    int rowDiff = destRow - srcRow;
    int colDiff = abs(destCol - srcCol);

    if (color == WHITE) {
        // White pawn moves upwards
        if (srcRow == 1 && rowDiff == 2 && colDiff == 0 && board[srcRow + 1][srcCol] == nullptr && board[destRow][destCol] == nullptr) {
            // Two-step forward movement from the starting position, only if the squares are empty
            return true;
        } else if (rowDiff == 1 && colDiff == 0 && board[destRow][destCol] == nullptr) {
            // One-step forward move, only if the destination square is empty
            return true;
        } else if (rowDiff == 1 && colDiff == 1 && board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() == BLACK) {
            // Diagonal capture move, only if the destination square contains an opponent's piece
            return true;
        }
    } else {
        // Black pawns move downwards
        if (srcRow == 6 && rowDiff == -2 && colDiff == 0 && board[srcRow - 1][srcCol] == nullptr && board[destRow][destCol] == nullptr) {
            // Two-step move from the starting position, only if the squares are empty
            return true;
        } else if (rowDiff == -1 && colDiff == 0 && board[destRow][destCol] == nullptr) {
            // One-step move forward, only if the destination square is empty
            return true;
        } else if (rowDiff == -1 && colDiff == 1 && board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() == WHITE) {
            // Diagonal capture move, only if the destination square contains an opponent's piece
            return true;
        }
    }

    return false;
}