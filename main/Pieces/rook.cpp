#include "rook.hpp"

Rook::Rook(PieceColor color): Piece(color,"Rook"){};

bool Rook::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8])  {
    //to check if it is in the same row or same col
    if (srcRow != destRow && srcCol != destCol) {
        return false;
    }
    //to check if there are any pieces blocking the path
    int rowStep = 0;
    int colStep = 0;

    if(destRow > srcRow) {
        rowStep = 1;
    } else if (destRow < srcRow) {
        rowStep = -1;
    }

    if(destCol > srcCol) {
        colStep = 1;
    } else if (destCol < srcCol) {
        colStep = -1;
    }
    int row = srcRow + rowStep;
    int col = srcCol + colStep;

    while(row != destRow || col != destCol) {
        if(board[row][col] != nullptr){
            return false;
        }
        row += rowStep;
        col += colStep;
    }
    //check destination is empty or occupied by opponent piece
    if (board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() == getColor()) {
        return false;
    }

    return true;

}