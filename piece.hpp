#ifndef PIECE_H
#define PIECE_H

#include <string>

enum PieceColor {WHITE, BLACK};

class Piece {
    protected: 
        PieceColor color;
        std::string name;
    public:
        Piece(PieceColor color, std::string name);
        virtual ~Piece();

        PieceColor getColor() const;
        std::string getName() const;

        virtual bool IsValidMove(int srcRow, int srcCol, 
        int destRow, int destCol) = 0;
};



#endif PIECE_H