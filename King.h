#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(Color color, char symbol);
    PieceType getType()const override;
    bool isValidMove(const Board&, const Move&, Color, bool allowBackwardJump) const override;
};