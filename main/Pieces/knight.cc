#include "knight.hpp"

Knight::Knight(PieceColor color): Piece(color,"Knight"){};

bool Knight::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    if(destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
        return false;
    }
    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);

    if((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        Piece* destPiece = board[destRow][destCol];
        if(destPiece == nullptr || destPiece -> getColor() != color) {
            return true;
        }
    }
    return false;
};