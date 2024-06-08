#ifndef BOARD_H
#define BOARD_H
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

private:
    void placePieces();
    void clearBoard();
    void findKing(PieceColor kingColor, int& kingRow, int& kingCol);
    PieceColor oppositeColor(PieceColor color);
    Move lastMove;
    PieceColor currentPlayer;
};

#endif