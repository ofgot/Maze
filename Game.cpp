//
// Created by Daria Kuznetsova on 03.09.2024.
//

#include <raylib.h>
#include "Coords.h"
#include "Game.h"
#include "GameState.h"

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
        }
    }
}

GameState Game::processGame() {
    while (!WindowShouldClose()) {
        update();

        for (auto& button : gameButtons) {
            button.handleInput(GetMousePosition());
        }

        MenuAction action = inputHandler.processGameButtons(gameButtons);

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

    for (auto& button : menuButtons) {
        button.handleInput(GetMousePosition());
    }

    render.menuRender(windowWidth, windowHeight, menuButtons );
    MenuAction action = inputHandler.processMenuButtons(menuButtons);

    switch (action) {
        case MenuAction::Start:
            gameInit();
            return GameState::Playing;
        case MenuAction::Load:
//            loadGame();
            return GameState::Playing;
        case MenuAction::Exit:
            return GameState::Exiting;
        case MenuAction::None:
        default:
            return GameState::Menu;
    }
}

void Game::generateButtonsForMenu() {
    Button startButton({170, 125, 200, 50}, "Start Game", 20, false,LIGHTGRAY, DARKGRAY, BLACK, WHITE);

    Button loadButton({170, 195, 200, 50}, "Load Game", 20, false,LIGHTGRAY, DARKGRAY, BLACK, WHITE);
    Button exitButton({170, 265, 200, 50}, "Exit", 20, false,LIGHTGRAY, DARKGRAY, BLACK, WHITE);

    menuButtons.push_back(startButton);
    menuButtons.push_back(loadButton);
    menuButtons.push_back(exitButton);
}

void Game::generateButtonsForGame() {
    Button backToMenuButton({ 5, 10, 100, 25 }, "Back to menu", 15, false, LIGHTGRAY, GRAY, BLACK, WHITE);
    gameButtons.push_back(backToMenuButton);
}

