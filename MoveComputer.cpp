#include "MoveComputer.h"
#include <iostream>
std::vector<Move> MoveComputer::getAllLegalMoves(const Board& board, Color playerColor){
    std::vector<Move> allMoves;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Position pos{row, col};
            auto piece = board.getPiece(pos);
            
            if (piece && piece->getColor() == playerColor) {
                auto moves = piece->getLegalMoves(board, pos);
                allMoves.insert(allMoves.end(), moves.begin(), moves.end()); //inserts to allMoves evry move in moves
            }
        }
    }
    return allMoves;
}
