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
    virtual std::vector<Direction> getDirections()const=0;


    // Check if the move is legal for a given color
    virtual bool isValidMove(const Board& board, const Move& move, Color playerColor)const = 0;
    // Get all valid moves for a specific piece at pos
    virtual std::vector<Move> getLegalMoves(const Board& board, const Position& pos)=0;
    // Get all jump moves for a given position - chain only
    // virtual std::vector<Move> getChainJumpMoves(const Board& board, const Position& pos)=0; // TODO - implement
};
