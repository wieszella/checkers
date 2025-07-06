#pragma once
// Forward declarations
class Board;

#include "Position.h"
#include "Board.h"
#include "Move.h"
#include <vector>
#include <map>

enum class Color {RED, BLACK};
enum class PieceType {KING, SOLDIER};

struct Direction {
    int dRow;
    int dCol;
};

const std::map<std::pair<Color, PieceType>, std::vector<Direction>> DirectionMap = {
    {{Color::RED, PieceType::KING} , {{1, -1}, {1, 1}, {-1, -1}, {-1, 1}}},
    {{Color::RED, PieceType::SOLDIER},{{1, -1}, {1, 1}}},
    {{Color::BLACK, PieceType::KING} , {{1, -1}, {1, 1}, {-1, -1}, {-1, 1}}},
    {{Color::BLACK, PieceType::SOLDIER},{{-1, -1}, {-1, 1}}},
};

class Piece {
protected:
    Color color;
    char symbol;

public:
    Piece(Color c, char s);
    virtual ~Piece() = default;

    virtual Color getColor() const;
    virtual char getSymbol()const;
    
    virtual PieceType getType()const = 0;
    virtual bool isValidMove(const Board&, const Move&, Color,std::vector<Direction>) const = 0;
};
