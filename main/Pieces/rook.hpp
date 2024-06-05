#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook: public Piece {
    public : 
    Rook(PieceColor color);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;

};


#endif