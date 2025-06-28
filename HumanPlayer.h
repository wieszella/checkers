#pragma once
#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    Move getMove(Board &board) override;
    Move getChainMove(Board &board, std::vector<Move> jumps)override;
};
// TODO - add to the human player a name and option to choose symbol. validate symbol.