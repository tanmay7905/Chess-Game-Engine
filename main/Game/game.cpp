#include "game.hpp"
#include <iostream>

Game::Game() : board(), gameTree(board) {}

void Game::run() {
    printInstructions();

    while (!isGameOver()) {
        board.printBoard();
        playMove();
    }

    board.printBoard();
    printGameResult();
}

void Game::printInstructions() {
    std::cout << "Welcome to Chess!\n";
    std::cout << "Enter moves using algebraic notation (e.g., e2e4, f7f5).\n";
    std::cout << "Type 'quit' to end the game.\n";
    std::cout << "Let's begin!\n\n";
}

void Game::playMove() {
    if (board.getCurrentPlayer() == WHITE) {
        // Human player's turn
        std::string move;
        std::cout << "Enter your move: ";
        std::cin >> move;

        if (move == "quit") {
            std::cout << "Game ended by user.\n";
            exit(0);
        }

             // Parse the move string
        if (move.length() != 4) {
            std::cout << "Invalid move format. Please enter a valid move (e.g., e2e4).\n";
            return;
        }

        // Convert algebraic notation to source and target positions
        int sourceCol = move[0] - 'a';
        int sourceRow = 8 - (move[1] - '0');
        int targetCol = move[2] - 'a';
        int targetRow = 8 - (move[3] - '0');

        // Validate the move
        if (!board.isValidMove(sourceRow, sourceCol, targetRow, targetCol)) {
            std::cout << "Invalid move. Please enter a valid move.\n";
            return;
        }

        // Make the move
        board.makeMove(sourceRow, sourceCol, targetRow, targetCol);

    } else {
        // AI player's turn
        std::cout << "AI player's turn...\n";
        gameTree.buildTree(4); // Set the desired search depth
        Move bestMove = gameTree.getBestMove();
        board.makeMove(bestMove);
    }
}

bool Game::isGameOver() {
    bool whiteKingCaptured = board.isCheckmate(WHITE) || board.isStalemate(WHITE);
    bool blackKingCaptured = board.isCheckmate(BLACK) || board.isStalemate(BLACK);
    return whiteKingCaptured || blackKingCaptured;
}

void Game::printGameResult() {
    if (board.isCheckmate(WHITE) || board.isStalemate(WHITE)) {
        std::cout << "Black wins! Checkmate.\n";
    } else if (board.isCheckmate(BLACK) || board.isStalemate(BLACK)) {
        std::cout << "White wins! Checkmate.\n";
    } else {
        std::cout << "Game ended in a draw.\n";
    }
}