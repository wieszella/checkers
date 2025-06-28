#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(Color color, char symbol);
    ~King()=default;
    bool (*getValidator())(const Board& board, const Move &move, Color color)override;
    static bool isValidMove(const Board& board, const Move &move, Color color);
};