//
// Created by Daria Kuznetsova on 01.11.2024.
//

#include "InputHandler.h"

void InputHandler::processInput(Player &player, Field &field) {
    size_t nextX = player.getX();
    size_t nextY = player.getY();

    if (IsKeyDown(KEY_W) && nextY > 0 && field.getField()[nextY - 1][nextX] == ' ' || field.getField()[nextY - 1][nextX] == '0') {
        player.moveUp();
    }

    if (IsKeyDown(KEY_S) && nextY < field.getY() - 1 && field.getField()[nextY + 1][nextX] == ' ' || field.getField()[nextY + 1][nextX] == '0') {
        player.moveDown();
    }

    if (IsKeyDown(KEY_A) && nextX > 0 && field.getField()[nextY][nextX - 1] == ' ' || field.getField()[nextY][nextX - 1] == '0') {
        player.moveLeft();
    }

    if (IsKeyDown(KEY_D) && nextX < field.getX() - 1 && field.getField()[nextY][nextX + 1] == ' ' || field.getField()[nextY][nextX + 1] == '0') {
        player.moveRight();
    }
}
