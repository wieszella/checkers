#include "Soldier.h"
#include <cmath>

Soldier::Soldier(Color Color, char symbol) : Piece(color, symbol)
{
    const std::vector<Direction> RED_DIRECTIONS = {{1, -1}, {1, 1}};
    const std::vector<Direction> BLACK_DIRECTIONS = {{-1, -1}, {-1, 1}};   
    direction = color == Color::RED ? RED_DIRECTIONS : BLACK_DIRECTIONS;
}

std::vector<Direction> Soldier::getDirections()const{
    return direction;
}

bool Soldier::isValidMove(const Board& board, const Move& move, Color playerColor)const{
    //the validation that both "from" and "to" are in the board is done outside this function
    auto piece = board.getPiece(move.from);
    
    //check if a player chose a piece that belongs to him
    if(!piece || piece->getColor() != playerColor) return false;

    //check if the position the player wants to move to is empty
    if(!board.isEmpty(move.to)) return false;

    //check that  move was done in the right direction
    // TODO - replace if color to generic direction
    if(piece->getColor() == Color::RED)
    {
        if(move.from.row == move.to.row + 1 && abs(move.from.col - move.to.col) == 1) return true; //normal step
        if(move.from.row == move.to.row + 2 && abs(move.from.col - move.to.col) == 2){ //eat
            int midRow = (move.from.row + move.to.row) / 2;
            int midCol = (move.from.col + move.to.col) / 2;
            auto betweenPiece = board.getPiece({midRow, midCol});
            return betweenPiece->getColor() == Color::BLACK;
        }
        return false;
    }
    else
    {
        if(move.from.row == move.to.row - 1 && abs(move.from.col - move.to.col) == 1) return true; //normal step
        if(move.from.row == move.to.row - 2 && abs(move.from.col - move.to.col) == 2){ //eat
            int midRow = (move.from.row + move.to.row) / 2;
            int midCol = (move.from.col + move.to.col) / 2;
            auto betweenPiece = board.getPiece({midRow, midCol});
            return betweenPiece->getColor() == Color::RED;
        }
        return false;
    }
}

std::vector<Move> Soldier::getLegalMoves(const Board& board, const Position& pos){
    std::vector<Move> legalMoves;
    auto piece = board.getPiece(pos);
    if (!piece) return legalMoves;

    Color color = piece->getColor();

    // Check normal (non-jump) moves
    for (const auto& dir : direction) {
        Position to{pos.row + dir.dRow, pos.col + dir.dCol};
        if (board.isInsideBoard(to) && board.isEmpty(to)) {
            legalMoves.push_back({pos, to});
        }
    }

    // Check jump moves
    for (const auto& dir : direction) {
        Position over{pos.row + dir.dRow, pos.col + dir.dCol};
        Position to{pos.row + 2 * dir.dRow, pos.col + 2 * dir.dCol};

        if (!board.isInsideBoard(to)) continue;

        auto middle = board.getPiece(over);
        if (middle && middle->getColor() != color && board.isEmpty(to)) {
            legalMoves.push_back({pos, to});
        }
    }
    return legalMoves;
}
// TODO - implement
// std::vector<Move> Soldier::getChainJumpMoves(const Board& board, const Position& pos);