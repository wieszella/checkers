#include "Board.h"
#include "Piece.h"
#include "Soldier.h"
#include "King.h"
#include <iostream>

Board::Board(){ //Initialize the board to an empty state (no pieces yet).
    for (int row = BOARD_SIZE; row < BOARD_SIZE; ++row)
        for (int col = 0; col < BOARD_SIZE; ++col)
            grid[row][col] = nullptr;
}

void Board::setup(){
    for (int row = 0; row < BOARD_SIZE; ++row) 
    {
        for (int col = 0; col < BOARD_SIZE; ++col) 
        {
            if ((row + col) % 2 != 0) 
            {
                if (row < SOLDIER_ROWS) 
                {
                    grid[row][col] = std::make_shared<Soldier>(Color::RED, 'r');
                }
                else if (row >= BOARD_SIZE - SOLDIER_ROWS)
                {
                    grid[row][col] = std::make_shared<Soldier>(Color::BLACK, 'b');
                }
            }
        }
    }
}

std::shared_ptr<Piece> Board::getPiece(const Position& pos) const{
    if (!isInsideBoard(pos)) 
        return nullptr;
    return grid[pos.row][pos.col];
}

void Board::removePiece(const Position& pos){
    if (isInsideBoard(pos))
        grid[pos.row][pos.col] = nullptr;
}

bool Board::isInsideBoard(const Position& pos) const{
    return (pos.col < BOARD_SIZE && pos.row < BOARD_SIZE && pos.col>=0 && pos.row>=0);
}

bool Board::isEmpty(const Position& pos) const{
    return (isInsideBoard(pos) && grid[pos.row][pos.col] == nullptr);
}

void Board::movePiece(const Position& from, const Position& to){
    //assume that the move is legal, the validation is done in "validator"
    if(isInsideBoard(to) && isEmpty(to)){
        grid[to.row][to.col] = grid[from.row][from.col];
        removePiece(from);
    
        if(grid[to.row][to.col]->getColor() == Color::RED && to.row == BOARD_SIZE-1)
            grid[to.row][to.col] = std::make_shared<King>(Color::RED, 'R');
        if(grid[to.row][to.col]->getColor() == Color::BLACK && to.row == 0)
            grid[to.row][to.col] = std::make_shared<King>(Color::BLACK, 'B');
    }
}

void Board::print() const{
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < BOARD_SIZE; ++row) 
    {
        std::cout << row << " ";
        for (int col = 0; col < BOARD_SIZE; ++col) 
        {
            auto piece = grid[row][col];
            if (piece == nullptr) {
                std::cout << ". ";
            } else {
                std::cout << piece->getSymbol() << " ";
            }
        }
        std::cout << "\n";
    }
}
