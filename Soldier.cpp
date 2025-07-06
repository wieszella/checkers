#include "Soldier.h"
#include <cmath>

Soldier::Soldier(Color color, char symbol) : Piece(color, symbol){}

PieceType Soldier::getType()const{ return PieceType::SOLDIER;}

bool Soldier::isValidMove(const Board& board, const Move& move, Color playerColor, std::vector<Direction> directions)const{
    if(!board.isInsideBoard(move.from) || !board.isInsideBoard(move.to)) return false;

    auto piece = board.getPiece(move.from);
    
    //check if a player chose a piece that belongs to him
    if(!piece || piece->getColor() != playerColor) return false;

    //check if the position the player wants to move to is empty
    if(!board.isEmpty(move.to)) return false;

    for (Direction &dir : directions)
    {
        int step = dir.dRow;

        int rowDiff = move.to.row- move.from.row;
        int colDiff = abs(move.to.col - move.from.col);

        if (rowDiff == step && colDiff == 1) {//normal step
            return true;
        }

        if(colDiff == 2) { //jump
            int midRow = (move.from.row + move.to.row) / 2;
            int midCol = (move.from.col + move.to.col) / 2;
            auto betweenPiece = board.getPiece({midRow, midCol});
            if(betweenPiece && betweenPiece->getColor() != piece->getColor())
            {//oponnent piece
                if(rowDiff == 2 * step) return true;
            }
        }

    }
    return false;
}