#pragma once
#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    Move getMove(const Board& board) override; 
};
// TODO - add to the human player a name and option to choose symbol. validate symbol.