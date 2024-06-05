#include "pawn.hpp"

Pawn::Pawn(PieceColor color): Piece(color,"Pawn"){};

bool Pawn::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    //To check that move is within the board
    if(destRow < 0 || destRow >= 8 || destCol < 0|| destCol >= 8) {
        return false;
    }

    int rowDiff = destRow - srcRow;
    int colDiff = destCol - srcCol;

    if(color == WHITE) {
        //if white pawn moves upwards
        if(srcRow == 1 && rowDiff == 2 && colDiff == 0) {
            //two step forward movement from the starting position
            return true;
        } else if(rowDiff == 1 && colDiff == 0) {
            return true;
        } else if (rowDiff == 1 && (colDiff == -1 || colDiff == 1)) {
            return true;
        }
    }     else {
        // Black pawns move downwards
        if (srcRow == 6 && rowDiff == -2 && colDiff == 0) {
            // Allow two-step move from the starting position
            return true;
        }
        else if (rowDiff == -1 && colDiff == 0) {
            // Allow one-step move forward
            return true;
        }
        else if (rowDiff == -1 && (colDiff == -1 || colDiff == 1)) {
            // Allow diagonal capture moves
            return true;
        }
    }
    return false;
}