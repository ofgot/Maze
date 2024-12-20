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
    std::cout << "How to start game?" << std::endl;
    std::cout << "Sequentially write this code:" << std::endl;
    std::cout << "brew install raylib" << std::endl;
    std::cout << "mkdir build" << std::endl;
    std::cout << "cd build" << std::endl;
    std::cout << "cmake .." << std::endl;
    std::cout << "cmake --build ." << std::endl;
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
