#include "Game.h"
#include <iostream>

Game::Game(std::shared_ptr<Player> red, std::shared_ptr<Player> black)
    : redPlayer(red), blackPlayer(black), currentTurn(Color::RED) {
    board.setup();
}

void Game::switchTurn(){
    currentTurn = (currentTurn == Color::RED) ? Color::BLACK : Color::RED;
}

std::shared_ptr<Player> Game::currentPlayer() {
    return (currentTurn == Color::RED) ? redPlayer : blackPlayer;
}

bool Game::hasLegalMoves(Color color) const {
    return !moveGenerator->getAllLegalMoves(board, color).empty();
}

void Game::play() {
    while (true) {
        system("cls");
        board.print();

        //end game condition
        if (!hasLegalMoves(currentTurn)) {
            std::cout << "Game over! " << (currentTurn == Color::RED ? "Black" : "Red") << " wins.\n";
            break;
        }

        std::cout << (currentTurn == Color::RED ? "Red" : "Black") << "'s turn.\n";

        Move move;
        bool valid = false;
        auto player = currentPlayer();

        //intake players move
        do {
            move =player->getMove(board);
            
            valid = board.getPiece(move.from)->isValidMove(board, move, currentTurn);

            if (!valid) {
                std::cout << "Invalid move. Try again.\n";
            }

        } while (!valid);

        //apply the move
        bool isEat = moveGenerator->isEatMove(board, move, currentTurn);
        moveExecutor->apply(board, move);

        while (isEat) {
            auto moves = moveGenerator->getLegalMovesForPos(board, move.to);
            auto jumps = moveGenerator->getChainJumps(board, moves, currentTurn);

            auto move = player->getChainMove(board, jumps);
            if (!move.empty){
                isEat = moveGenerator->isEatMove(board, move, currentTurn);
                moveExecutor->apply(board, move);
            } else{
                isEat = false;
            }
            
        }
        switchTurn();
    }
}
