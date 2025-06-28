#include <iostream>
#include <memory>
#include "Game.h"
#include "HumanPlayer.h"
#include "Player.h"

int main() {
    std::cout << "Welcome to Console Checkers!\n\n";

    std::shared_ptr<Player> redPlayer = std::make_shared<HumanPlayer>();
    std::shared_ptr<Player> blackPlayer = std::make_shared<HumanPlayer>();

    // Start game
    Game game(std::move(redPlayer), std::move(blackPlayer));
    game.play();

    std::cout << "\nThanks for playing!\n";
    return 0;
}
