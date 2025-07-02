#pragma once
#include "Board.h"
#include "Move.h"
#include "Piece.h"

class MoveGenerator {
public:
    bool isEatMove(const Board& board, Move& move, Color playerColor);
    
    std::vector<Move> getChainJumps(const Board& board, std::vector<Move> moves, Color playerColor);

    std::vector<Move> getLegalMovesForPos(const Board&, const Position& pos);
    
    // Get all legal moves for a player (used to detect if game is over)
    std::vector<Move> getAllLegalMoves(const Board& board, Color playerColor);

    // Get all jump moves for a given position - chain only
    std::vector<Move> getChainJumpMoves(const Board& board, const Position& pos);
    
};