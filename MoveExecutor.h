#pragma once
#include "Board.h"
#include "Move.h"

class MoveExecutor {
public:
    static void apply(Board& board, const Move& move);
    static void eat(Board& board, const Move& move);
};
