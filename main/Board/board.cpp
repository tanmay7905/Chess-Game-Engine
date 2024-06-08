#include "board.hpp"
#include <iostream>


Board::Board() : lastMove(-1, -1, -1, -1, nullptr), currentPlayer(WHITE) {
    resetBoard();
}

Board::~Board() {
    clearBoard();
}

void Board::resetBoard() {
    clearBoard();
    placePieces();
}

void Board::printBoard() {
    std::cout << " a b c d e f g h" << std::endl;
    for(int row = 7; row >= 0; --row) {
        std::cout << row + 1 << " ";
        for(int col = 0; col < 8; ++col){
            Piece* piece = board[row][col];
            if(piece == nullptr){
                std::cout << ". ";
            } else {
                char pieceChar; 
                if(dynamic_cast<Pawn*>(piece) != nullptr) {
                    pieceChar = 'P';
                } else if(dynamic_cast<Knight*>(piece) != nullptr) {
                    pieceChar = 'N';
                } else if(dynamic_cast<Bishop*>(piece) != nullptr) {
                    pieceChar = 'B';
                } else if (dynamic_cast<Rook*>(piece)!= nullptr) {
                    pieceChar = 'R';
                } else if(dynamic_cast<Queen*>(piece) != nullptr) {
                    pieceChar = 'Q';
                } else if(dynamic_cast<King*>(piece) != nullptr) {
                    pieceChar = 'K';
                }

                if(piece ->getColor() == WHITE) {
                    pieceChar = std::toupper(pieceChar);
                } else {
                    pieceChar = std::tolower(pieceChar);
                }

                std::cout << pieceChar << " ";
            }
        }
        std::cout << row + 1 << std::endl;
    }
    std::cout <<" a b c d e f g h" << std::endl;
}

void Board::makeMove(const Move& move) {
    int srcRow = move.getSourceRow();
    int srcCol = move.getSourceColumn();
    int destRow = move.getDestinationRow();
    int destCol = move.getDestinationColumn();
    Piece* movedPiece = move.getMovedPiece();
    Piece* capturedPiece = move.getCapturedPiece();

    // Update the board
    board[destRow][destCol] = movedPiece;
    board[srcRow][srcCol] = nullptr;

    // Update the last move
    lastMove = move;

    // Update the current player
    currentPlayer = oppositeColor(currentPlayer);

    // Delete the captured piece
    delete capturedPiece;
}

bool Board::isValidMove(const Move& move) {
    
    int srcRow = move.getSourceRow();
    int srcCol = move.getSourceColumn();
    int destRow = move.getDestinationRow();
    int destCol = move.getDestinationColumn();
    Piece* movedPiece = move.getMovedPiece();

    // Check if the source square contains a piece of the current player's color
    if (board[srcRow][srcCol] == nullptr || board[srcRow][srcCol]->getColor() != currentPlayer) {
        return false;
    }
     // Check if the moved piece matches the piece on the source square
    if (board[srcRow][srcCol] != movedPiece) {
        return false;
    }
     // Check if the destination square is within the board boundaries
    if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
        return false;
    }
    // Check if the destination square is occupied by a piece of the same color
    if (board[destRow][destCol] != nullptr && board[destRow][destCol]->getColor() == currentPlayer) {
        return false;
    }
    // Check if the move is valid for the specific piece type
    if (!movedPiece->isValidMove(srcRow, srcCol, destRow, destCol, board)) {
        return false;
    }
    // Check if the move puts the current player's king in check
    Piece* capturedPiece = board[destRow][destCol];
    board[destRow][destCol] = movedPiece;
    board[srcRow][srcCol] = nullptr;

    bool isKingInCheck = this->isKingInCheck(currentPlayer);

    board[srcRow][srcCol] = movedPiece;
    board[destRow][destCol] = capturedPiece;

    if (isKingInCheck) {
        return false;
    }
    return true;
}

std::vector<Move> Board::generateLegalMoves(PieceColor color) {
    // Implement the logic to generate legal moves for a given color
    std::vector<Move> legalMoves; 
    for(int row = 0; row < 8; ++row) {
        for(int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if(piece != nullptr && piece ->getColor() == color) {
                for(int destRow = 0; destRow < 8; ++destRow) {
                    for(int destCol = 0; destCol < 8; ++destCol) {
                        Move move(row, col, destRow, destCol, piece); 
                        if(isValidMove(move)) {
                            legalMoves.push_back(move);
                        }
                    }
                }
            }
        }
    }
    return legalMoves;
}

bool Board::isSquareAttacked(int row, int col, PieceColor attackerColor) {
    // Check if the square is attacked by a pawn
    int pawnRow = (attackerColor == WHITE) ? row - 1 : row + 1;
    if (pawnRow >= 0 && pawnRow < 8) {
        if (col > 0 && board[pawnRow][col - 1] != nullptr &&
            board[pawnRow][col - 1]->getColor() == attackerColor &&
            dynamic_cast<Pawn*>(board[pawnRow][col - 1]) != nullptr) {
            return true;
        }
        if (col < 7 && board[pawnRow][col + 1] != nullptr &&
            board[pawnRow][col + 1]->getColor() == attackerColor &&
            dynamic_cast<Pawn*>(board[pawnRow][col + 1]) != nullptr) {
            return true;
        }
    }

    // Check if the square is attacked by a knight
    int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    for (int i = 0; i < 8; ++i) {
        int knightRow = row + knightMoves[i][0];
        int knightCol = col + knightMoves[i][1];
        if (knightRow >= 0 && knightRow < 8 && knightCol >= 0 && knightCol < 8 &&
            board[knightRow][knightCol] != nullptr &&
            board[knightRow][knightCol]->getColor() == attackerColor &&
            dynamic_cast<Knight*>(board[knightRow][knightCol]) != nullptr) {
            return true;
        }
    }

    // Check if the square is attacked by a bishop or a queen (diagonal)
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int i = 0; i < 4; ++i) {
        int attackRow = row + directions[i][0];
        int attackCol = col + directions[i][1];
        while (attackRow >= 0 && attackRow < 8 && attackCol >= 0 && attackCol < 8) {
            if (board[attackRow][attackCol] != nullptr) {
                if (board[attackRow][attackCol]->getColor() == attackerColor &&
                    (dynamic_cast<Bishop*>(board[attackRow][attackCol]) != nullptr || dynamic_cast<Queen*>(board[attackRow][attackCol]) != nullptr)) {
                    return true;
                }
                break;
            }
            attackRow += directions[i][0];
            attackCol += directions[i][1];
        }
    }

    // Check if the square is attacked by a rook or a queen (horizontal/vertical)
    int directions2[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    for (int i = 0; i < 4; ++i) {
        int attackRow = row + directions2[i][0];
        int attackCol = col + directions2[i][1];
        while (attackRow >= 0 && attackRow < 8 && attackCol >= 0 && attackCol < 8) {
            if (board[attackRow][attackCol] != nullptr) {
                if (board[attackRow][attackCol]->getColor() == attackerColor &&
                    (dynamic_cast<Rook*>(board[attackRow][attackCol]) != nullptr || dynamic_cast<Queen*>(board[attackRow][attackCol]) != nullptr)) {
                    return true;
                }
                break;
            }
            attackRow += directions2[i][0];
            attackCol += directions2[i][1];
        }
    }

    // Check if the square is attacked by a king
    int kingMoves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 8; ++i) {
        int kingRow = row + kingMoves[i][0];
        int kingCol = col + kingMoves[i][1];
        if (kingRow >= 0 && kingRow < 8 && kingCol >= 0 && kingCol < 8 &&
            board[kingRow][kingCol] != nullptr &&
            board[kingRow][kingCol]->getColor() == attackerColor &&
            dynamic_cast<King*>(board[kingRow][kingCol]) != nullptr) {
            return true;
        }
    }

    return false;
}

bool Board::isKingInCheck(PieceColor kingColor) {
    int kingRow, kingCol;
    findKing(kingColor, kingRow, kingCol);
    return isSquareAttacked(kingRow, kingCol, oppositeColor(kingColor));
}

bool Board::isCheckmate(PieceColor kingColor) {
    if (!isKingInCheck(kingColor)) {
        return false;
    }

    std::vector<Move> legalMoves = generateLegalMoves(kingColor);
    for (const Move& move : legalMoves) {
        // Make the move
        Piece* capturedPiece = board[move.getDestinationRow()][move.getDestinationColumn()];
        board[move.getDestinationRow()][move.getDestinationColumn()] = move.getMovedPiece();
        board[move.getSourceRow()][move.getSourceColumn()] = nullptr;

        // Check if the king is still in check after the move
        bool isStillInCheck = isKingInCheck(kingColor);

        // Undo the move
        board[move.getSourceRow()][move.getSourceColumn()] = move.getMovedPiece();
        board[move.getDestinationRow()][move.getDestinationColumn()] = capturedPiece;

        if (!isStillInCheck) {
            return false;
        }
    }

    return true;
}

bool Board::isStalemate(PieceColor kingColor) {
    if (isKingInCheck(kingColor)) {
        return false;
    }

    std::vector<Move> legalMoves = generateLegalMoves(kingColor);
    return legalMoves.empty();
}

std::string Board::getBoardHash() {
    std::string fen = "";

    // Iterate over each row of the board
    for (int row = 7; row >= 0; --row) {
        int emptySquares = 0;

        // Iterate over each column of the board
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];

            if (piece == nullptr) {
                emptySquares++;
            } else {
                if (emptySquares > 0) {
                    fen += std::to_string(emptySquares);
                    emptySquares = 0;
                }

                char pieceChar;
                if (dynamic_cast<Pawn*>(piece) != nullptr) {
                    pieceChar = 'P';
                } else if (dynamic_cast<Knight*>(piece) != nullptr) {
                    pieceChar = 'N';
                } else if (dynamic_cast<Bishop*>(piece) != nullptr) {
                    pieceChar = 'B';
                } else if (dynamic_cast<Rook*>(piece) != nullptr) {
                    pieceChar = 'R';
                } else if (dynamic_cast<Queen*>(piece) != nullptr) {
                    pieceChar = 'Q';
                } else if (dynamic_cast<King*>(piece) != nullptr) {
                    pieceChar = 'K';
                }

                if (piece->getColor() == BLACK) {
                    pieceChar = std::tolower(pieceChar);
                }

                fen += pieceChar;
            }
        }

        if (emptySquares > 0) {
            fen += std::to_string(emptySquares);
        }

        if (row > 0) {
            fen += "/";
        }
    }

    // Add the current player's turn to the FEN string
    fen += " ";
    fen += (currentPlayer == WHITE) ? "w" : "b";

    return fen;
}

Move Board::getLastMove() const {
    return lastMove;
}

PieceColor Board::getCurrentPlayer() const {
    return currentPlayer;
}

void Board::placePieces() {
    // White pieces
    board[0][0] = new Rook(WHITE);
    board[0][1] = new Knight(WHITE);
    board[0][2] = new Bishop(WHITE);
    board[0][3] = new Queen(WHITE);
    board[0][4] = new King(WHITE);
    board[0][5] = new Bishop(WHITE);
    board[0][6] = new Knight(WHITE);
    board[0][7] = new Rook(WHITE);

    for (int col = 0; col < 8; ++col) {
        board[1][col] = new Pawn(WHITE);
    }

    // Black pieces
    board[7][0] = new Rook(BLACK);
    board[7][1] = new Knight(BLACK);
    board[7][2] = new Bishop(BLACK);
    board[7][3] = new Queen(BLACK);
    board[7][4] = new King(BLACK);
    board[7][5] = new Bishop(BLACK);
    board[7][6] = new Knight(BLACK);
    board[7][7] = new Rook(BLACK);

    for (int col = 0; col < 8; ++col) {
        board[6][col] = new Pawn(BLACK);
    }
}

void Board::clearBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete board[row][col];
            board[row][col] = nullptr;
        }
    }
}

void Board::findKing(PieceColor kingColor, int& kingRow, int& kingCol) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board[row][col] != nullptr && board[row][col]->getColor() == kingColor &&
                dynamic_cast<King*>(board[row][col]) != nullptr) {
                kingRow = row;
                kingCol = col;
                return;
            }
        }
    }
}

PieceColor Board::oppositeColor(PieceColor color) const {
    return (color == WHITE) ? BLACK : WHITE;
}