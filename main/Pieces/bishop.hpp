#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"

class Bishop: public Piece {
public:
    Bishop(PieceColor color);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;
};

#endif // BISHOP_HPP