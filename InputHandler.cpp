//
// Created by Daria Kuznetsova on 01.11.2024.
//

#include "InputHandler.h"
#include "Button.h"

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

MenuAction InputHandler::processMenuButtons(std::vector<Button>& buttons) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        for (auto& button : buttons) {
            if (CheckCollisionPointRec(GetMousePosition(), button.getRect())) {
                if (strcmp(button.getText(), "Start Game") == 0) { // return 0 if texts are the same
                    return MenuAction::Start;
                } else if (strcmp(button.getText(), "Load Game") == 0) {
                    return MenuAction::Load;
                } else if (strcmp(button.getText(), "Exit") == 0) {
                    return MenuAction::Exit;
                }
            }
        }
    }
    return MenuAction::None;
}

GameState InputHandler::processGameButtons(std::vector<Button>& buttons) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        for (auto& button : buttons) {
            if (CheckCollisionPointRec(GetMousePosition(), button.getRect())) {
                if (strcmp(button.getText(), "Start Game") == 0) { // return 0 if texts are the same
                    return GameState::Menu;
                }
            }
        }
    }
}
