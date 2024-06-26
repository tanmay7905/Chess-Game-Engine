#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>
#include <string>
#include "Pieces/piece.hpp"
#include "move.hpp"
#include "Pieces/pawn.hpp"
#include "Pieces/knight.hpp"
#include "Pieces/bishop.hpp"
#include "Pieces/rook.hpp"
#include "Pieces/queen.hpp"
#include "Pieces/king.hpp"

class Board {
private:
    Piece* board[8][8];
public:
    Board();
    ~Board();
    void resetBoard();
    void printBoard();
    void makeMove(const Move& move);
    bool isValidMove(const Move& move);
    std::vector<Move> generateLegalMoves(PieceColor color);
    bool isSquareAttacked(int row, int col, PieceColor attackerColor);
    bool isKingInCheck(PieceColor kingColor);
    bool isCheckmate(PieceColor kingColor);
    bool isStalemate(PieceColor kingColor);
    std::string getBoardHash();
    Move getLastMove();
    PieceColor getCurrentPlayer();
    Move getLastMove() const;
    void findKing(PieceColor kingColor, int& kingRow, int& kingCol);
    PieceColor getCurrentPlayer() const;
    bool isValidSquare(int row, int col) const;

    Piece *getPiece(int row, int col) const;

    void makeMove(int sourceRow, int sourceCol, int targetRow, int targetCol);

    bool isValidMove(int sourceRow, int sourceCol, int targetRow, int targetCol);
    int getTotalPieces() const;

private:
    void placePieces();
    void clearBoard();
    PieceColor oppositeColor(PieceColor color) const;
    
    Move lastMove;
    PieceColor currentPlayer;
};

#endif