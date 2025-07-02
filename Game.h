#pragma once
#include "Board.h"
#include "IPlayer.h"
#include "MoveGenerator.h"
#include "MoveExecutor.h"
#include <memory>

class Game {
private:
    Board board;
    std::shared_ptr<Player> redPlayer;
    std::shared_ptr<Player> blackPlayer;
    Color currentTurn;

    std::unique_ptr<MoveGenerator> moveGenerator;
    std::unique_ptr<MoveExecutor> moveExecutor;
    
    std::shared_ptr<Player> currentPlayer();
    void switchTurn();
    bool hasLegalMoves(Color color) const;
public:
    Game(std::shared_ptr<Player> red, std::shared_ptr<Player> black);
    void play();
    
};
