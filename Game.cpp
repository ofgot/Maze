//
// Created by Daria Kuznetsova on 03.09.2024.
//

#include <raylib.h>
#include "Coords.h"
#include "Game.h"
#include "GameState.h"
#include "DialogWindow.h"
#include "fstream"

//generate field and window
void Game::gameInit() {
    field.generateField();
    Coords startPos = field.getStartPosition();
    player.setPosition(startPos.getX(), startPos.getY());

    int newWidth = static_cast<int>(field.getX()) * render.getTileSize();
    int newHeight = static_cast<int>(field.getY()) * render.getTileSize();
    SetWindowSize(newWidth, newHeight + panel);
}

void Game::run() {
    render.gameRenderInit(windowWidth, windowHeight);
    generateButtonsForMenu();
    generateButtonsForGame();

    GameState state = GameState::Menu;
    while (!WindowShouldClose()) {
        switch (state) {
            case GameState::Menu:
                state = processMenu();
                break;
            case GameState::Playing:
                state = processGame();
                break;
            case GameState::Exiting:
                CloseWindow();
                break;
            case GameState::None:
                break;
        }
    }
}

GameState Game::processGame() {
    while (!WindowShouldClose()) {
        update();

        for (auto &button: gameButtons) {
            button.handleInput(GetMousePosition());
        }

        GameState action = inputHandler.processGameButtons(gameButtons);
        if (action == GameState::Menu) {
            generateButtonForConfirmation(field.getX() * render.getTileSize(), field.getY() * render.getTileSize());
            generateDialogWindowConfirmation(field.getX() * render.getTileSize(), field.getY() * render.getTileSize());
            confirmationWindows[0].activate();

            while (confirmationWindows[0].isActive) {
                confirmationWindows[0].render();

                if (confirmationWindows[0].getResult() != DialogResult::None) {
                    if (confirmationWindows[0].getResult() == DialogResult::Yes) {
                        saveLoadGame.saveGameField("savedField.bin", field.getField());
                        saveLoadGame.savePLayer("savedOther.bin", field, player);
                    }
                    confirmationWindows[0].deactivate();
                    return GameState::Menu;
                }
            }
        }

        render.render(field, player, gameButtons[0]);
    }
    return GameState::Exiting;
}

void Game::update() {
    inputHandler.processInput(player, field);

    if (field.getField()[player.getY()][player.getX()] == '0') {
        gameInit();
    }

}

GameState Game::processMenu() {
    SetWindowSize(windowWidth, windowHeight);

    for (auto &button: menuButtons) {
        button.handleInput(GetMousePosition());
    }

    render.menuRender(windowWidth, windowHeight, menuButtons);
    MenuState action = inputHandler.processMenuButtons(menuButtons);

    switch (action) {
        case MenuState::Start:
            gameInit();
            return GameState::Playing;
        case MenuState::Load:
            if (saveLoadGame.loadField("savedField.bin", field) && saveLoadGame.loadPLayer("savedOther.bin", player, field)){
                SetWindowSize(field.getX() * render.getTileSize(), field.getY() * render.getTileSize() + panel);
                return GameState::Playing;
            } else {
                return GameState::Menu;
            }
        case MenuState::Exit:
            return GameState::Exiting;
        case MenuState::None:
        default:
            return GameState::Menu;
    }
}

void Game::generateButtonsForMenu() {
    Button startButton({170, 125, 200, 50}, "Start Game", 20, false, LIGHTGRAY, DARKGRAY, BLACK, WHITE);

    Button loadButton({170, 195, 200, 50}, "Load Game", 20, false, LIGHTGRAY, DARKGRAY, BLACK, WHITE);
    Button exitButton({170, 265, 200, 50}, "Exit", 20, false, LIGHTGRAY, DARKGRAY, BLACK, WHITE);

    menuButtons.push_back(startButton);
    menuButtons.push_back(loadButton);
    menuButtons.push_back(exitButton);
}

void Game::generateButtonsForGame() {
    Button backToMenuButton({5, 10, 100, 25}, "Back to menu", 15, false, LIGHTGRAY, GRAY, BLACK, WHITE);
    gameButtons.push_back(backToMenuButton);
}

void Game::generateButtonForConfirmation(int x, int y) {
    confirmationButtons.clear();

    float xt = ((x - 300) / 2) + (300 / 2) - 25;
    float yt = ((y - 200) / 2) + (200 / 2);

    Button yes({xt - 35, yt, 50, 25}, "Yes", 15, false, DARKGRAY, GRAY, WHITE, BLACK);
    Button no({xt + 35, yt, 50, 25}, "No", 15, false, DARKGRAY, GRAY, WHITE, BLACK);
    confirmationButtons.push_back(yes);
    confirmationButtons.push_back(no);
}

void Game::generateDialogWindowConfirmation(int x, int y) {
    confirmationWindows.clear();
    DialogWindow dialog("Do you want to save game?", "Yes", "No", confirmationButtons, x,
                        y, false);

    confirmationWindows.push_back(dialog);
}