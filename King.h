#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(Color color, char symbol);
    bool isValidMove(const Board&, const Move&, Color) const override;
};