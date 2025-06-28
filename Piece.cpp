#include "Piece.h"

Piece::Piece(Color color, char c) : color(color), symbol(c){}

Piece::~Piece()=default; // TODO - why??

char Piece::getSymbol()const
{
    return symbol;
}

Color Piece::getColor() const
{
    return color;
}

std::vector<Direction> Piece::getDirections()const{
    return direction;
}
