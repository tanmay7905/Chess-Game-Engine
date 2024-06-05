#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"

class Queen: public Piece {
    public : 
    Queen(PieceColor color);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;
};




#endif