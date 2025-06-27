#include "Position.h"

bool Position::operator==(const Position& other)const{
    return col == other.col && row == other.row;
}

bool Position::operator!=(const Position& other)const{
    return !(*this == other);
}