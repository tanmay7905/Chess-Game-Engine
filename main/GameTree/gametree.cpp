#include "gametree.hpp"

GameTree::GameTree(const Board& initialBoard) {
    root = new Node{initialBoard, {}};
}

GameTree::~GameTree() {
    freeTree(root);
}

void GameTree::buildTree(int depth) {
    expandNode(root, depth);
}

int GameTree::alphaBeta(Node* node, int depth, int alpha, int beta, bool maximizingPlayer) {
    if(depth == 0 || node->children.empty()) {
        return evaluateBoard(node -> board);
    }

    if(maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for(Node* child : node->children) {
            int eval = alphaBeta(child, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if(beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
            for (Node* child : node->children) {
            int eval = alphaBeta(child, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;  // Alpha cut-off
            }
        }
        return minEval;
    }
}

Move GameTree::getBestMove() {
    int maxEval = std::numeric_limits<int>::min();
    Move bestMove;

    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    for (Node* child : root->children) {
        int eval = alphaBeta(child, 3, alpha, beta, false);
        if (eval > maxEval) {
            maxEval = eval;
            bestMove = child->board.getLastMove();
        }
    }

    return bestMove;
}


void GameTree::expandNode(Node* node, int depth) {
    if (depth == 0) {
        return;
    }

    std::vector<Move> legalMoves = node->board.generateLegalMoves(node->board.getCurrentPlayer());
    for (const Move& move : legalMoves) {
        Board newBoard = node->board;
        newBoard.makeMove(move);

        std::string boardHash = newBoard.getBoardHash();
        if (transpositionTable.find(boardHash) == transpositionTable.end()) {
            Node* newNode = new Node{newBoard, {}};
            node->children.push_back(newNode);
            transpositionTable[boardHash] = newNode;
            expandNode(newNode, depth - 1);
        }
    }
}

void GameTree::freeTree(Node* node) {
    for (Node* child : node->children) {
        freeTree(child);
    }
    delete node;
}

int GameTree::evaluateBoard(Board& board) {
    int score = 0;

    // Iterate over the board and evaluate each piece
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.getPiece(row, col);
            if (piece != nullptr) {
                int pieceValue = 0;
                
                // Assign values to each piece type
                if (piece->getName() == "Pawn") {
                    pieceValue = 100;
                } else if (piece->getName() == "Knight" || piece->getName() == "Bishop") {
                    pieceValue = 300;
                } else if (piece->getName() == "Rook") {
                    pieceValue = 500;
                } else if (piece->getName() == "Queen") {
                    pieceValue = 900;
                } else if (piece->getName() == "King") {
                    pieceValue = 10000;
                }

                // Multiply the piece value by 1 for white and -1 for black
                if (piece->getColor() == WHITE) {
                    score += pieceValue;
                } else {
                    score -= pieceValue;
                }
            }
        }
    }

    // Evaluate king safety
    int whiteKingSafety = evaluateKingSafety(board, WHITE);
    int blackKingSafety = evaluateKingSafety(board, BLACK);
    score += whiteKingSafety - blackKingSafety;

    // Adjust evaluation based on the stage of the game
    int totalPieces = board.getTotalPieces();
    if (totalPieces <= 16) {
        // End-game: Prioritize king safety and mobility
        score += (whiteKingSafety - blackKingSafety) * 2;
        score += evaluateKingMobility(board, WHITE) - evaluateKingMobility(board, BLACK);
    }

    return score;
}

int GameTree::evaluateKingSafety(Board& board, PieceColor color) {
    int kingSafety = 0;

    // Find the king's position
    int kingRow, kingCol;
    board.findKing(color, kingRow, kingCol);

    // Check if the king is in check
    if (board.isSquareAttacked(kingRow, kingCol, color == WHITE ? BLACK : WHITE)) {
        kingSafety -= 100;
    }

    // Check if the king has friendly pieces nearby for protection
    int friendlyPieces = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int row = kingRow + i;
            int col = kingCol + j;
            if (board.isValidSquare(row, col)) {
                Piece* piece = board.getPiece(row, col);
                if (piece != nullptr && piece->getColor() == color) {
                    ++friendlyPieces;
                }
            }
        }
    }
    kingSafety += friendlyPieces * 10;

    return kingSafety;
}

int GameTree::evaluateKingMobility(Board& board, PieceColor color) {
    int kingMobility = 0;

    // Find the king's position
    int kingRow, kingCol;
    board.findKing(color, kingRow, kingCol);

    // Count the number of safe squares the king can move to
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            int row = kingRow + i;
            int col = kingCol + j;
            if (board.isValidSquare(row, col) && !board.isSquareAttacked(row, col, color == WHITE ? BLACK : WHITE)) {
                ++kingMobility;
            }
        }
    }

    return kingMobility;
}