#include "Game.h"
#include <iostream>

Game::Game(std::shared_ptr<Player> red, std::shared_ptr<Player> black) // TODO - go over initilizer
    : redPlayer(std::move(red)), blackPlayer(std::move(black)), currentTurn(Color::RED) {
    board.setup();
}

void Game::switchTurn(){
    currentTurn = (currentTurn == Color::RED) ? Color::BLACK : Color::RED;
}

void Game::eat(const Move &move){
        // Determine the step direction for x and y
        int stepX = ((move.from.row - move.to.row) > 0) ? -1 : 1;
        int stepY = ((move.from.col - move.to.col) > 0) ? -1 : 1;

        Position currentPoint = move.from;

        for (int i = 0; i < std::abs(move.from.row - move.to.row) - 1; i++) {
            currentPoint.row += stepX;
            currentPoint.col += stepY;
            board.removePiece(currentPoint);
        }
}

void Game::play() {
    while (true) {
        board.print();

        //end game condition
        auto legalMoves = MoveComputer::getAllLegalMoves(board, currentTurn);
        if (legalMoves.empty()) {
            std::cout << "Game over! " << (currentTurn == Color::RED ? "Black" : "Red") << " wins.\n"; // TODO - replace with name
            break;
        }

        std::cout << (currentTurn == Color::RED ? "Red" : "Black") << "'s turn.\n";

        Move move;
        bool valid = false;
        auto player = (currentTurn == Color::RED) ? redPlayer : blackPlayer;
        //intake players move
        do {
            move =player->getMove(board);
            
            auto validator = board.getPiece(move.from)->getValidator();
            valid = validator(board, move, currentTurn);

            if (!valid) {
                std::cout << "Invalid move. Try again.\n";
            }

        } while (!valid);

        //apply the move
        board.movePiece(move.from, move.to);

        while (MoveComputer::isEatMove(board, move, currentTurn)) {
            //clear the pieces between the positions of the jump
            eat(move);

            // TODO! - implement chain eating 
            auto moves = MoveComputer::getLegalMovesForPos(board, move.to);
            auto jumps = MoveComputer::getChainJumps(board, moves, currentTurn);

            move = player->getChainMove(board, jumps);

            if (!move.empty){
                board.movePiece(move.from, move.to);
            }  
        }
        switchTurn();
    }
}