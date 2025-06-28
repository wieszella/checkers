#pragma once
#include "Position.h"

struct Move {
    Position from;
    Position to;
    bool empty;

    Move(Position fromPos, Position toPos):from(fromPos), to(toPos), empty(false){};
    Move(): empty(true){};
    bool operator==(const Move& other) const
    {
        return (from == other.from && to == other.to && empty == other.empty);
    }
};
