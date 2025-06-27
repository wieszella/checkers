#pragma once
#include "Piece.h"

class Soldier : public Piece {
public:
    Soldier(Color Color, char symbol);
    std::vector<Direction> getDirections()const override;
    ~Soldier()=default;

    bool isValidMove(const Board& board, const Move& move, Color playerColor)const override;
    std::vector<Move> getLegalMoves(const Board& board, const Position& pos)override;
    std::vector<Move> getChainJumpMoves(const Board& board, const Position& pos)override;
};
