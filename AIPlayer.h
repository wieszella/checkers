#pragma once
#include "Player.h"

class AIPlayer : public Player {
public:
    Move getMove(const Board& board) override;
};