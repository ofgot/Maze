#include <iostream>
#include "Field.h"
#include "Game.h"
#include "GameRender.h"

int main() {
//    GameRender gr;
//    gr.init();

//    Field f;
//    f.generateField();
//    f.draw();

//    std::cout << "\033[?25l";
//    Game game;
//    game.run();
//    std::cout << "\033[?25h";

    Game game; // Создание объекта игры
    game.init(); // Инициализация игры
    game.run(); // Запуск игрового цикла
    return 0;
}
