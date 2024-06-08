#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn: public Piece {
public:
    Pawn(PieceColor color);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;
};

#endif // PAWN_HPP