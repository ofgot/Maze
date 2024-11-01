//
// Created by Daria Kuznetsova on 01.11.2024.
//

#include "InputHandler.h"

void InputHandler::processInput(Player &player) {
    if (IsKeyDown(KEY_W)) {
        player.moveUp();
    }

    if (IsKeyDown(KEY_S)) {
        player.moveDown();
    }

    if (IsKeyDown(KEY_A)) {
        player.moveLeft();
    }

    if (IsKeyDown(KEY_D)) {
        player.moveRight();
    }
}
