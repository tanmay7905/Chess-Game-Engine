#ifndef GAME_H
#define GAME_H

#include "Board/board.hpp"
#include "GameTree/gametree.hpp"

class Game {
private:
    Board board;
    GameTree gameTree;

public:
    Game();

    void run();

private:
    void printInstructions();
    void playMove();
    bool isGameOver();
    void printGameResult();
};

#endif