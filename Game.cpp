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

    GameState state = GameState::Menu;
    while (!WindowShouldClose()) {
        switch (state) {
            case GameState::Menu:
                state = processMenu();
                break;
            case GameState::Playing:
                state = processGame();
                break;
            case GameState::Paused:
                // pausse
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

        //back to menu

        if (inputHandler.isButtonClicked({10, 10, 100, 30})) {
            return GameState::Menu;
        }

        render.render(field, player);
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
    render.menuRender(windowWidth, windowHeight);
    std::vector<Button> but = render.getMenuButtons(GetScreenWidth(), GetScreenHeight());
    MenuAction action = inputHandler.processMenuButtons(but);

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
