#pragma once
#include "Board.h"
#include "Move.h"

class Player {
public:
    virtual Move getMove(const Board& board) = 0;
    virtual ~Player() = default;
};
