#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"

class King: public Piece {
    public : 
    King(PieceColor color);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override ;
};




#endif