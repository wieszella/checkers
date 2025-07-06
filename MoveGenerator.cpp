#include "MoveGenerator.h"
#include <iostream>

std::vector<Move> MoveGenerator::getLegalMovesForPos(const Board& board, const Position& pos, bool allowBackwardJump){
    std::vector<Move> legalMoves;
    auto piece = board.getPiece(pos);
    if (!piece) return legalMoves;

    Color color = piece->getColor();
    
    const auto& directions = allowBackwardJump 
    ? DirectionMap.at({color, PieceType::KING})
    : DirectionMap.at({color, PieceType::SOLDIER});
    
    for (const auto& dir : directions) {
        int r = pos.row + dir.dRow;
        int c = pos.col + dir.dCol;
        
        while (board.isInsideBoard({r, c})) {
            Move move{pos, {r, c}};
            
            if (piece->isValidMove(board, move, color, directions))
            legalMoves.push_back(move);
            r += dir.dRow;
            c += dir.dCol;
        }
    }
    return legalMoves;
}

std::vector<Move> MoveGenerator::getAllLegalMoves(const Board& board, Color playerColor){
    std::vector<Move> allMoves;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Position pos{row, col};
            auto piece = board.getPiece(pos);
            
            if (piece && piece->getColor() == playerColor) {
                auto moves = getLegalMovesForPos(board, pos, false);
                allMoves.insert(allMoves.end(), moves.begin(), moves.end()); //inserts to allMoves evry move in moves
            }
        }
    }
    return allMoves;
}

bool MoveGenerator::isEatMove(const Board& board, Move& validMove, Color playerColor){
    if(validMove.empty) return false;

    auto piece = board.getPiece(validMove.from);
    int stepX = ((validMove.from.row - validMove.to.row) > 0) ? -1 : 1;
    int stepY = ((validMove.from.col - validMove.to.col) > 0) ? -1 : 1;

    bool isOpponentPiece = false;
    Position currentPoint = validMove.from;

    for (int i = 0; i < std::abs(validMove.from.row - validMove.to.row) - 1; i++) {
        currentPoint.row += stepX;
        currentPoint.col += stepY;
        if(!board.isEmpty(currentPoint) && playerColor != board.getPiece(currentPoint)->getColor()){
            return true;
        }
    }
    return false;
}

std::vector<Move> MoveGenerator::getChainJumps(const Board& board, std::vector<Move> moves, Color playerColor){
    std::vector<Move> jumps;
    for(Move move:moves){
        if(isEatMove(board, move, playerColor))
            jumps.push_back(move);
    }
    return jumps;
}
