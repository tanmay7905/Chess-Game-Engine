#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight: public Piece {
public:
    Knight(PieceColor color);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;
};

#endif // KNIGHT_HPP