#include <iostream>
#include <memory>
#include "Game.h"
#include "HumanPlayer.h"
#include "IPlayer.h"
#include "AIPlayer.h"

int main() {
    std::cout << "Welcome to Console Checkers!\n\n";

    std::string res;
    std::shared_ptr<Player> redPlayer = std::make_shared<HumanPlayer>();
    std::shared_ptr<Player> blackHumanPlayer = std::make_shared<HumanPlayer>();
    std::shared_ptr<Player> blackAIPlayer = std::make_shared<AIPlayer>(Color::BLACK);
    // std::shared_ptr<Player> redAIPlayer = std::make_shared<AIPlayer>(Color::RED);
    
    do
    {
        std::cout << "do you want to play againt a human(1) or a machine(2)?" << std::endl;
        std::cin >> res;
    } while(res != "1" && res != "2");
    // Start game
    std::shared_ptr<Player> blackPlayer = (res == "1") ? blackHumanPlayer : blackAIPlayer;
    Game game(redPlayer, blackPlayer);
    // Game game(redAIPlayer, blackAIPlayer);
    game.play();

    std::cout << "\nThanks for playing!\n";
    return 0;
}
