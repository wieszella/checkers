#pragma once
#include "Piece.h"

class Soldier : public Piece {
public:
    Soldier(Color color, char symbol);
    PieceType getType()const override;
    bool isValidMove(const Board&, const Move&, Color,std::vector<Direction>) const override;
};
