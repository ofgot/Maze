//
// Created by Daria Kuznetsova on 03.09.2024.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H


#include "Field.h"
#include "Player.h"
#include "GameRender.h"
#include "InputHandler.h"
#include "raylib.h"
#include "GameState.h"
#include "DialogWindow.h"

class Game {
private:
    Field field;
    Player player;
    GameRender render;
    InputHandler inputHandler;

    const int panel = 40;
    const size_t windowWidth = 540;
    const size_t windowHeight = 400;

    std::vector<Button> menuButtons;
    std::vector<Button> gameButtons;
    std::vector<Button> confirmationButtons;

public:
    Game() = default;
    void gameInit();
    void run();
    void update();
    GameState processMenu();
    GameState processGame();

    void generateButtonsForMenu();

    void generateButtonsForGame();

    void generateButtonForConfirmation();
};


#endif //MAZE_GAME_H
