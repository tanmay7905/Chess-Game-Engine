#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight: public Piece {
    public : 
    Knight(PieceColor color);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol) ;
};




#endif