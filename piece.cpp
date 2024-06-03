#include "piece.hpp" 

Piece::Piece(PieceColor color, std::string name) : color(color), name(name) {};

Piece::~Piece() {}

PieceColor Piece::getColor() const {
    return color;
}

std::string Piece::getName() const {
    return name;
}