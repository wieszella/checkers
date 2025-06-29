#include "MoveComputer.h"
#include <iostream>

std::vector<Move> MoveComputer::getLegalMovesForPos(const Board& board, const Position& pos){
    std::vector<Move> legalMoves;
    auto piece = board.getPiece(pos);
    if (!piece) return legalMoves;

    Color color = piece->getColor();
    auto validator = board.getPiece(pos)->getValidator();

    for (const auto& dir : piece->getDirections()) {
        int r = pos.row + dir.dRow;
        int c = pos.col + dir.dCol;
        
        while (board.isInsideBoard({r, c})) {
            Position moveTo = {r, c};
            Move moveToCheck = {pos, moveTo};
            
            bool valid = validator(board, moveToCheck, color);
            if(valid)
            legalMoves.push_back(moveToCheck);
            r += dir.dRow;
            c += dir.dCol;
        }
    }
    return legalMoves;
}

std::vector<Move> MoveComputer::getAllLegalMoves(const Board& board, Color playerColor){
    std::vector<Move> allMoves;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Position pos{row, col};
            auto piece = board.getPiece(pos);
            
            if (piece && piece->getColor() == playerColor) {
                auto moves = getLegalMovesForPos(board, pos);
                allMoves.insert(allMoves.end(), moves.begin(), moves.end()); //inserts to allMoves evry move in moves
            }
        }
    }
    return allMoves;
}

bool MoveComputer::isEatMove(const Board& board, Move& validMove, Color playerColor){
    if(validMove.empty) return false;

    auto piece = board.getPiece(validMove.from);
    int stepX = ((validMove.from.row - validMove.to.row) > 0) ? -1 : 1;
    int stepY = ((validMove.from.col - validMove.to.col) > 0) ? -1 : 1;

    bool isOpponentPiece = false;
    Position currentPoint = validMove.from;

    for (int i = 0; i < std::abs(validMove.from.row - validMove.to.row) - 1; i++) {
        currentPoint.row += stepX;
        currentPoint.col += stepY;
        if(!board.isEmpty(currentPoint)){
            return true;
        }
    }
    return false;
}

std::vector<Move> MoveComputer::getChainJumps(const Board& board, std::vector<Move> moves, Color playerColor){
    std::vector<Move> jumps;
    for(Move move:moves){
        if(isEatMove(board, move, playerColor))
            jumps.push_back(move);
    }
    return jumps;
}
