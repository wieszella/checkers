#pragma once
// Forward declarations
class Board;

#include "Position.h"
#include "Board.h"
#include "Move.h"
#include <vector>


enum class Color {RED, BLACK};

struct Direction {
    int dRow;
    int dCol;
};

class Piece {
protected:
    Color color;
    char symbol;
    std::vector<Direction> direction;

public:
    Piece(Color c, char s);
    virtual ~Piece() = default;

    virtual Color getColor() const;
    virtual char getSymbol()const;
    virtual std::vector<Direction> getDirections()const;
    
    virtual bool isValidMove(const Board&, const Move&, Color) const = 0;
};
