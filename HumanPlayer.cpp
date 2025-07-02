#include "HumanPlayer.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>


bool HumanPlayer::isNumeric(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

HumanPlayer::HumanPlayer(){}

Move HumanPlayer::getMove(Board &board){
    Position from, to;
    while (true) {
        std::string x, y;
        std::cout << "Enter the row and column of the piece you want to move (for example, 2 3): \n";
        std::cin >> x >> y;

        if (!isNumeric(x) || !isNumeric(y)) {
            std::cout << "Invalid input. Try again.\n";
            continue;
        } else{
            from.row = stoi(x);
            from.col = stoi(y);
        }

        if (board.isEmpty(from)) {
            std::cout << "Invalid place. Try again.\n";
            continue;
        }

        std::cout << "Enter the row and column of the destination square (for example, 3 4): \n";
        std::cin >> x >> y;

        if (!isNumeric(x) || !isNumeric(y)) {
            std::cout << "Invalid input. Try again.\n";
            continue;
        }else{
            to.row = stoi(x);
            to.col = stoi(y);
        }

        return Move{from, to};
    }
}

Move HumanPlayer::getChainMove(Board &board, std::vector<Move> jumps){
    char response;
    Move chain = Move();
    if (!jumps.empty()) {
        do{
            std::cout << "Jump available. Chain? (y/n): ";
            while((response = toupper(getchar())) == '\n');
        }while(response != 'Y' && response != 'N');
        
        if(response == 'Y'){
            do {
                board.print();
                chain = getMove(board);
            } while(std::count(jumps.begin(), jumps.end(), chain) == 0);
        }
    }
    return chain;
}
