#include "King.h"
#include <cmath>

King::King(Color color, char symbol) : Piece(color, symbol){}

PieceType King::getType()const{return PieceType::KING;}

bool King::isValidMove(const Board& board, const Move& move, Color playerColor, std::vector<Direction> directions)const{
    if(!board.isInsideBoard(move.from) || !board.isInsideBoard(move.to)) return false;
    
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