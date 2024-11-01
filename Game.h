//
// Created by Daria Kuznetsova on 03.09.2024.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H


#include "Field.h"
#include "Player.h"
#include "GameRender.h"
#include "InputHandler.h"
#include "raylib.h"

class Game {
private:
    Field field;
    Player player;
    GameRender render;
    InputHandler inputHandler;
public:
    Game() = default;
    void init();
    void run();
    void update();
};

#endif //MAZE_GAME_H
