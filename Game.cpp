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
                        saveGameField();
                        saveOther();
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
            std::cout << "start" << std::endl;
            if (loadGame() && loadOther()){
                std::cout << "in" << std::endl;
                SetWindowSize(field.getX() * render.getTileSize(), field.getY() * render.getTileSize() + panel);
                return GameState::Playing;
            } else {
                std::cout << "smt wrong" << std::endl;
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

bool Game::saveGameField() {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ofstream outFile(projectRoot + "/savedField.bin", std::ios::binary | std::ios::trunc);

        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for saving: savedField.bin" << std::endl;
            return false;
        }

        const auto &fiel = field.getField();
        for (const auto &row: fiel) {
            size_t rowSize = row.size();
            outFile.write(reinterpret_cast<const char *>(&rowSize), sizeof(rowSize));
            outFile.write(row.data(), rowSize);
        }

        std::cout << "Game saved successfully!" << std::endl;
        outFile.close();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error saving game: " << e.what() << std::endl;
        return false;
    }
}

bool Game::loadGame() {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ifstream inFile(projectRoot + "/savedField.bin", std::ios::binary);

        if (!inFile.is_open()) {
            std::cerr << "Failed to open file for loading: savedField.bin" << std::endl;
            return false;
        }

        std::vector<std::vector<char>> fieldData;
        size_t rowSize = 0;
        while (inFile.read(reinterpret_cast<char *>(&rowSize), sizeof(rowSize))) {
            std::vector<char> row(rowSize);
            inFile.read(row.data(), rowSize);
            fieldData.push_back(row);
        }

        field.setField(fieldData);
        inFile.close();

        std::cout << "Field loaded successfully!" << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error loading game: " << e.what() << std::endl;
        return false;
    }
}

bool Game::saveOther() {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ofstream outFile(projectRoot + "/savedOther.bin", std::ios::binary | std::ios::trunc);
        std::cout << "Game saved to: " << projectRoot + "/src/savedField.bin" << std::endl;

        size_t x = field.getX();
        size_t y = field.getY();
        size_t startX = field.getStartPosition().getX();
        size_t startY = field.getStartPosition().getY();
        size_t endX = field.getExitPosition().getX();
        size_t endY = field.getExitPosition().getY();
        size_t playerX = player.getX();
        size_t playerY = player.getY();

        outFile.write(reinterpret_cast<const char *>(&x), sizeof(x));
        outFile.write(reinterpret_cast<const char *>(&y), sizeof(y));
        outFile.write(reinterpret_cast<const char *>(&startX), sizeof(startX));
        outFile.write(reinterpret_cast<const char *>(&startY), sizeof(startY));
        outFile.write(reinterpret_cast<const char *>(&endX), sizeof(endX));
        outFile.write(reinterpret_cast<const char *>(&endY), sizeof(endY));

        outFile.write(reinterpret_cast<const char *>(&playerX), sizeof(playerX));
        outFile.write(reinterpret_cast<const char *>(&playerY), sizeof(playerY));

        std::cout << "Data for player and field saved successfully!" << std::endl;
        outFile.close();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error saving game: " << e.what() << std::endl;
        return false;
    }
}

bool Game::loadOther() {
    try {
        std::string projectRoot = std::__fs::filesystem::current_path().parent_path().string();
        std::ifstream inFile(projectRoot + "/savedOther.bin", std::ios::binary);

        if (!inFile.is_open()) {
            std::cerr << "Failed to open file for loading: savedField.bin" << std::endl;
            return false;
        }

        size_t x, y, startX, startY, endX, endY, playerX, playerY;

        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        inFile.read(reinterpret_cast<char*>(&startX), sizeof(startX));
        inFile.read(reinterpret_cast<char*>(&startY), sizeof(startY));
        inFile.read(reinterpret_cast<char*>(&endX), sizeof(endX));
        inFile.read(reinterpret_cast<char*>(&endY), sizeof(endY));
        inFile.read(reinterpret_cast<char*>(&playerX), sizeof(playerX));
        inFile.read(reinterpret_cast<char*>(&playerY), sizeof(playerY));

        field.setX(x);
        field.setY(y);
        field.setStartPosition(startX, startY);
        field.setExitPosition(endX, endY);

        player.setPosition(playerX, playerY);

        inFile.close();

        std::cout << "Data for player and field loaded successfully!" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error loading game: " << e.what() << std::endl;
        return false;
    }
}
