#include <iostream>
#include "Game.h"

void printHelp() {
    std::cout << "Usage: program [options]" << std::endl;
    std::cout << "--help       Show this help message" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Controls: " << std::endl;
    std::cout << "W: Move up" << std::endl;
    std::cout << "A: Move left" << std::endl;
    std::cout << "S: Move down" << std::endl;
    std::cout << "D: Move right" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "To start game just go to the Maze/built and run " << std::endl;
    std::cout << "./Maze" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--help") {
        printHelp();
        return 0;
    }

    Game game;
    game.run();

    return 0;
}
