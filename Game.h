#pragma once
#include "Board.h"
#include "Player.h"
#include "MoveComputer.h"
#include <memory>

class Game {
private:
    Board board;
    std::unique_ptr<Player> redPlayer;
    std::unique_ptr<Player> blackPlayer;
    Color currentTurn;

public:
    Game(std::unique_ptr<Player> red, std::unique_ptr<Player> black);
    void play();
    void switchTurn();
    void eat(const Move& move);
};
