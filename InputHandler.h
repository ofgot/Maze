//
// Created by Daria Kuznetsova on 01.11.2024.
//

#ifndef MAZE_INPUTHANDLER_H
#define MAZE_INPUTHANDLER_H
#include "Player.h"
#include "raylib.h"
#include "Field.h"
#include "Button.h"
#include "MenuAction.h"
#include "GameState.h"

class InputHandler {
public:
    void processInput(Player& player, Field& field);

    MenuAction processMenuButtons(std::vector<Button>& buttons);

    GameState processGameButtons(std::vector<Button>& buttons);
};


#endif //MAZE_INPUTHANDLER_H
