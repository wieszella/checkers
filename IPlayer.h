#pragma once
#include "Board.h"
#include "Move.h"

class Player {
public:
    virtual Move getMove(Board &board) = 0;
    virtual Move getChainMove(Board &board, std::vector<Move> jumps) = 0;
    virtual ~Player() = default;
};
