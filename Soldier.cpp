#include "Soldier.h"
#include <cmath>

Soldier::Soldier(Color color, char symbol) : Piece(color, symbol)
{
    const std::vector<Direction> RED_DIRECTIONS = {{1, -1}, {1, 1}};
    const std::vector<Direction> BLACK_DIRECTIONS = {{-1, -1}, {-1, 1}};   
    direction = color == Color::RED ? RED_DIRECTIONS : BLACK_DIRECTIONS;  
}

PieceType Soldier::getType()const{ return PieceType::SOLDIER;}

bool Soldier::isValidMove(const Board& board, const Move& move, Color playerColor, bool allowBackwardJump)const{
    if(!board.isInsideBoard(move.from) || !board.isInsideBoard(move.to)) return false;

    auto piece = board.getPiece(move.from);
    
    //check if a player chose a piece that belongs to him
    if(!piece || piece->getColor() != playerColor) return false;

    //check if the position the player wants to move to is empty
    if(!board.isEmpty(move.to)) return false;

    //check that  move was done in the right direction
    int step = (piece->getColor() == Color::RED) ? -1 : 1;   
    
    int rowDiff = move.from.row - move.to.row;
    int colDiff = abs(move.to.col - move.from.col);

    if (rowDiff == step && colDiff == 1) {//normal step
        return true;
    }

    if(colDiff == 2) { //jump
        int midRow = (move.from.row + move.to.row) / 2;
        int midCol = (move.from.col + move.to.col) / 2;
        auto betweenPiece = board.getPiece({midRow, midCol});
        if(betweenPiece && betweenPiece->getColor() != piece->getColor()){//oponnent piece
            if(rowDiff == 2 * step) return true;
            if(allowBackwardJump && abs(rowDiff) == 2) return true;
        }
    }
    return false;
}