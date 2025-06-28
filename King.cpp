#include "King.h"
#include <cmath>

King::King(Color color, char symbol) : Piece(color, symbol)
{
    direction = {{1, -1}, {1, 1}, {-1, -1}, {-1, 1}};
}

std::vector<Direction> King::getDirections()const{
    return direction;
}

bool King::isValidMove(const Board& board, const Move& move, Color playerColor)const{
    //the validation that both "from" and "to" are in the board is done outside this function
    auto piece = board.getPiece(move.from);
    
    //check if a player chose a piece that belongs to him
    if(!piece || piece->getColor() != playerColor) return false;

    //check if the position the player wants to move to is empty
    if(!board.isEmpty(move.to)) return false;

    //check that  move was done in a valid direction (aka diagnally)
    if(abs(move.from.row - move.to.row) != abs(move.from.col - move.to.col)) return false;

    // a king is allowed to move n steps as long as he doesnt jump over his own piece and more than one opponent piece
    // Determine the step direction for x and y
    int stepX = ((move.from.row - move.to.row) > 0) ? -1 : 1;
    int stepY = ((move.from.col - move.to.col) > 0) ? -1 : 1;

    bool isOpponentPiece = false;
    Position currentPoint = move.from;

    for (int i = 0; i < std::abs(move.from.row - move.to.row) - 1; i++) {
        currentPoint.row += stepX;
        currentPoint.col += stepY;
        if(!board.isEmpty(currentPoint) && board.getPiece(currentPoint)->getColor() == piece->getColor()) return false;
        else if(!board.isEmpty(currentPoint)){
            if(isOpponentPiece) return false;
            else isOpponentPiece = true;
        }
    }
    return true;
}

std::vector<Move> King::getLegalMoves(const Board& board, const Position& pos){
    std::vector<Move> legalMoves;
    auto piece = board.getPiece(pos);
    if (!piece) return legalMoves;

    Color color = piece->getColor();

    for (const auto& dir : direction) {
        int r = pos.row + dir.dRow;
        int c = pos.col + dir.dCol;
        
        while (board.isInsideBoard({r, c})) {
            Position moveTo = {r, c};
            Move moveToCheck = {pos, moveTo};
            if(isValidMove(board, moveToCheck, color))
            legalMoves.push_back(moveToCheck);
            r += dir.dRow;
            c += pos.col + dir.dCol;
        }
    }
    return legalMoves;
}

// TODO - implement
// std::vector<Move> isValidMove::getChainJumpMoves(const Board& board, const Position& pos){}