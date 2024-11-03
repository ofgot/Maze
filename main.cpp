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

    Game game;
    game.gameInit();
    game.run();
    return 0;

}
