#pragma once
#include "Board.h"
#include "Player.h"
#include "MoveComputer.h"
#include <memory>

class Game {
private:
    Board board;
    std::shared_ptr<Player> redPlayer;
    std::shared_ptr<Player> blackPlayer;
    Color currentTurn;

public:
    Game(std::shared_ptr<Player> red, std::shared_ptr<Player> black);
    void play();
    void switchTurn();
    void eat(const Move& move);
};
