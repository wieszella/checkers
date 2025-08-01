#pragma once
// Forward declarations
class Piece;
enum class Color;
enum class PieceType;

#include <memory>
#include <vector>
#include "Piece.h"
#include "Position.h"

const int BOARD_SIZE = 8;
const int SOLDIER_ROWS = 3;

class Board {
private:
    std::shared_ptr<Piece> grid[BOARD_SIZE][BOARD_SIZE];

public:
    Board();
    Board(const Board&);

    void setup();
    std::shared_ptr<Piece> getPiece(const Position& pos) const;
    void movePiece(const Position& from, const Position& to);
    void removePiece(const Position& pos);
    bool isInsideBoard(const Position& pos) const;
    bool isEmpty(const Position& pos) const;
    int countPieceColor(const Color& c, PieceType t)const;
    void print() const;
};
