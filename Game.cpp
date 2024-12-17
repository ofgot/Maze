//
// Created by Daria Kuznetsova on 03.09.2024.
//

#include <raylib.h>
#include "Coords.h"
#include "Game.h"
#include "GameState.h"
#include "DialogWindow.h"

// Initialize the game field and window size
void Game::gameInit() {
    field.generateField();
    Coords startPos = field.getStartPosition();
    player.setPosition(startPos.getX(), startPos.getY());

    int newWidth = static_cast<int>(field.getX()) * render.getTileSize();
    int newHeight = static_cast<int>(field.getY()) * render.getTileSize();
    SetWindowSize(newWidth, newHeight + panel);
}

// Main game loop
void Game::run() {
    // Initialize rendering for the game
    render.gameRenderInit(windowWidth, windowHeight);
    // Generate buttons for the menu and game
    generateButtonsForMenu();
    generateButtonsForGame();

    // Set the initial game state to Menu
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

// Process actions during the gameplay
GameState Game::processGame() {
    while (!WindowShouldClose()) {
        // Update the game state
        update();

        // Handle button inputs during the game
        for (auto &button: gameButtons) {
            button.handleInput(GetMousePosition());
        }

        // Process game buttons for possible actions
        GameState action = inputHandler.processGameButtons(gameButtons);
        if (action == GameState::Menu) {
            generateButtonForConfirmation(static_cast<int>(field.getX()) * render.getTileSize(), static_cast<int>(field.getY()) * render.getTileSize());
            generateDialogWindowConfirmation(static_cast<int>(field.getX()) * render.getTileSize(), static_cast<int>(field.getY()) * render.getTileSize());
            confirmationWindows[0].activate();

            // Wait for the confirmation window to close and process the result
            while (confirmationWindows[0].isActive) {
                confirmationWindows[0].render();

                // If the player selects an option, handle the result
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

// Update game state, including player movement
void Game::update() {
    inputHandler.processInput(player, field);

    if (field.getField()[player.getY()][player.getX()] == '0') {
        gameInit();
    }

}

// Process actions in the menu
GameState Game::processMenu() {
    SetWindowSize(static_cast<int>(windowWidth), static_cast<int>(windowHeight));

    for (auto &button: menuButtons) {
        button.handleInput(GetMousePosition());
    }

    render.menuRender(static_cast<float >(windowWidth), static_cast<float>(windowHeight), menuButtons);
    MenuState action = inputHandler.processMenuButtons(menuButtons);

    switch (action) {
        case MenuState::Start:
            gameInit();
            return GameState::Playing;
        case MenuState::Load:
            if (saveLoadGame.loadField("savedField.bin", field) && saveLoadGame.loadPLayer("savedOther.bin", player, field)){
                SetWindowSize(static_cast<int>(field.getX()) * render.getTileSize(), static_cast<int>(field.getY()) * render.getTileSize() + panel);
                return GameState::Playing;
            } else {
                // if there is no data it starts a new game
                gameInit();
                return GameState::Playing;
            }
        case MenuState::Exit:
            return GameState::Exiting;
        case MenuState::None:
        default:
            return GameState::Menu;
    }
}

// Generate buttons for the menu screen
void Game::generateButtonsForMenu() {
    Button startButton({170, 125, 200, 50}, "Start Game", 20, false, LIGHTGRAY, DARKGRAY, BLACK, WHITE);

    Button loadButton({170, 195, 200, 50}, "Load Game", 20, false, LIGHTGRAY, DARKGRAY, BLACK, WHITE);
    Button exitButton({170, 265, 200, 50}, "Exit", 20, false, LIGHTGRAY, DARKGRAY, BLACK, WHITE);

    menuButtons.push_back(startButton);
    menuButtons.push_back(loadButton);
    menuButtons.push_back(exitButton);
}

// Generate buttons for the in-game screen
void Game::generateButtonsForGame() {
    Button backToMenuButton({5, 10, 100, 25}, "Back to menu", 15, false, LIGHTGRAY, GRAY, BLACK, WHITE);
    gameButtons.push_back(backToMenuButton);
}

// Generate buttons for the confirmation dialog
void Game::generateButtonForConfirmation(int x, int y) {
    confirmationButtons.clear();

    float xt = (static_cast<float>(x - 300) / 2) + (static_cast<float>(300) / 2) - 25;
    float yt = (static_cast<float>(y - 200) / 2) + (static_cast<float>(200) / 2);

    Button yes({xt - 35, yt, 50, 25}, "Yes", 15, false, DARKGRAY, GRAY, WHITE, BLACK);
    Button no({xt + 35, yt, 50, 25}, "No", 15, false, DARKGRAY, GRAY, WHITE, BLACK);
    confirmationButtons.push_back(yes);
    confirmationButtons.push_back(no);
}

// Generate the dialog window for the confirmation
void Game::generateDialogWindowConfirmation(int x, int y) {
    confirmationWindows.clear();
    DialogWindow dialog("Do you want to save game?", "Yes", "No", confirmationButtons, x,
                        y, false);

    confirmationWindows.push_back(dialog);
}