#pragma once
#include "Piece.h"

class Soldier : public Piece {
public:
    Soldier(Color color, char symbol);
    ~Soldier()=default;
    bool (*getValidator())(const Board& board, const Move &move, Color color)override;
    static bool isValidMove(const Board& board, const Move &move, Color color);
};
