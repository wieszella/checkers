#include "HumanPlayer.h"
#include <iostream>
#include <string>
#include <cctype>


bool isNumeric(const std::string& str) { // TODO - deal with this function better
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

HumanPlayer::HumanPlayer(){}

Move HumanPlayer::getMove(const Board& board){
    Position from, to;
    while (true) {
        std::string x, y;
        std::cout << "Enter the row and column of the piece you want to move (for example, 2 3): ";
        std::cin >> x >> y;

        if (!isNumeric(x) || !isNumeric(y)) {
            std::cout << "Invalid input. Try again.\n";
            continue;
        } else{
            from.row = stoi(x);
            from.col = stoi(y);
            if(!board.isInsideBoard(from))
            {
                std::cout << "Invalid piece. Try again.\n";
                continue;
            }
        }

        std::cout << "Enter the row and column of the destination square (for example, 3 4): ";
        std::cin >> x >> y;

        if (!isNumeric(x) || !isNumeric(y)) {
            std::cout << "Invalid input. Try again.\n";
            continue;
        }else{
            to.row = stoi(x);
            to.col = stoi(y);
            if(!board.isInsideBoard(to))
            {
                std::cout << "Invalid destination. Try again.\n";
                continue;
            }
        }

        return Move{from, to};
    }
}