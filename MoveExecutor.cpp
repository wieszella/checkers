#include "MoveExecutor.h"
#include <cmath>

void MoveExecutor::eat(Board& board, const Move &move){
    // Determine the step direction for x and y
    int stepX = ((move.from.row - move.to.row) > 0) ? -1 : 1;
    int stepY = ((move.from.col - move.to.col) > 0) ? -1 : 1;

    Position currentPoint = move.from;

    for (int i = 0; i < std::abs(move.from.row - move.to.row) - 1; i++) {
        currentPoint.row += stepX;
        currentPoint.col += stepY;
        board.removePiece(currentPoint);
    }
}

void MoveExecutor::apply(Board& board, const Move& move) {
    board.movePiece(move.from, move.to);
    if (std::abs(move.from.row - move.to.row) > 1) {
        eat(board, move);
    }
}