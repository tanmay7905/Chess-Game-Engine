#ifndef MOVE_HPP
#define MOVE_HPP

#include "Pieces/piece.hpp"

class Move {
private:
    int srcRow;
    int srcCol;
    int destRow;
    int destCol;
    Piece* movedPiece;
    Piece* capturedPiece;

public:
    Move(int srcRow, int srcCol, int destRow, int destCol, Piece* movedPiece, Piece* capturedPiece = nullptr);
    Move() =default;
    int getSourceRow() const;
    int getSourceColumn() const;
    int getDestinationRow() const;
    int getDestinationColumn() const;
    Piece* getMovedPiece() const;
    Piece* getCapturedPiece() const;

    bool operator==(const Move& other) const;
};

#endif