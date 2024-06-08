#ifndef GAMETREE_HPP
#define GAMETREE_HPP

#include <vector>
#include <unordered_map>
#include "Board/board.hpp"
#include "Board/move.hpp"

class GameTree {
private:
    struct Node {
        Board board;
        std::vector<Node*> children;
    };

    Node* root;
    std::unordered_map<std::string, Node*> transpositionTable;

public:
    GameTree(const Board& initialBoard);
    ~GameTree();

    void buildTree(int depth);
    int alphaBeta(Node* node, int depth, int alpha, int beta, bool maximizingPlayer);
    Move getBestMove();

private:
    void expandNode(Node* node, int depth);
    int evaluateBoard(Board& board);
    int evaluateKingSafety(Board &board, PieceColor color);
    int evaluateKingMobility(Board &board, PieceColor color);
    void freeTree(Node *node);
};

#endif