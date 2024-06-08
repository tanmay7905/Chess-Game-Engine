#ifndef GAME_HPP
#define GAME_HPP

#include "Board/board.hpp"
#include "GameTree/gametree.hpp"
#include "Board/move.hpp"


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