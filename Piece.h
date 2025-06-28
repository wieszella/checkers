#pragma once
// Forward declarations
class Board;
struct Move;
struct Position;

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
    Piece(Color color, char c);
    virtual ~Piece() = 0;
    virtual Color getColor() const;
    virtual char getSymbol()const;
    virtual std::vector<Direction> getDirections()const;
    virtual bool (*getValidator())(const Board& board, const Move &move, Color color)=0;
};
