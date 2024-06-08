#include "move.hpp"

Move::Move(int srcRow, int srcCol, int destRow, int destCol, Piece* movedPiece, Piece* capturedPiece)
    : srcRow(srcRow), srcCol(srcCol), destRow(destRow), destCol(destCol),
      movedPiece(movedPiece), capturedPiece(capturedPiece) {}

int Move::getSourceRow() const {
    return srcRow;
}

int Move::getSourceColumn() const {
    return srcCol;
}

int Move::getDestinationRow() const {
    return destRow;
}

int Move::getDestinationColumn() const {
    return destCol;
}

Piece* Move::getMovedPiece() const {
    return movedPiece;
}

Piece* Move::getCapturedPiece() const {
    return capturedPiece;
}

bool Move::operator==(const Move& other) const {
    return (srcRow == other.srcRow && srcCol == other.srcCol &&
            destRow == other.destRow && destCol == other.destCol &&
            movedPiece == other.movedPiece && capturedPiece == other.capturedPiece);
}