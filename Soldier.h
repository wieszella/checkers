#pragma once
#include "Piece.h"

class Soldier : public Piece {
public:
    Soldier(Color color, char symbol);
    bool isValidMove(const Board&, const Move&, Color) const override;
};
