#include "Piece.h"

Piece::Piece(Color color, char c) : color(color), symbol(c){}

char Piece::getSymbol()const
{
    return symbol;
}

Color Piece::getColor() const
{
    return color;
}
