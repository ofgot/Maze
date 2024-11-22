//
// Created by Daria Kuznetsova on 01.11.2024.
//

#ifndef MAZE_INPUTHANDLER_H
#define MAZE_INPUTHANDLER_H
#include "Player.h"
#include "raylib.h"
#include "Field.h"
#include "Button.h"
#include "MenuState.h"
#include "GameState.h"

class InputHandler {
public:
    void processInput(Player& player, Field& field);

    MenuState processMenuButtons(std::vector<Button>& buttons);

    GameState processGameButtons(std::vector<Button>& buttons);
};


#endif //MAZE_INPUTHANDLER_H
