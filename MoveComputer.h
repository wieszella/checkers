#pragma once
#include "Board.h"
#include "Move.h"
#include "Piece.h"

class MoveComputer {
public:
    //functions used for AI
    // Get all legal moves for a player (used to detect if game is over)
    static std::vector<Move> getAllLegalMoves(const Board& board, Color playerColor);

    // Get all jump moves for a given position - chain only
    static std::vector<Move> getChainJumpMoves(const Board& board, const Position& pos);
};

// TODO - getChainJumpMoves