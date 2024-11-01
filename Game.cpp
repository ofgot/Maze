//
// Created by Daria Kuznetsova on 03.09.2024.
//

#include <thread>
#include "Game.h"


void Game::init() {
    field.generateField();
    Coords startPos = field.getStartPosition();
    player.setPosition(startPos.getX(), startPos.getY());
}

void Game::run() {
    render.init();

    while (!WindowShouldClose()) {
        update();
        render.render(field, player);
    }

    render.close();
}

void Game::update() {
    inputHandler.processInput(player);

    if (field.getField()[player.getY()][player.getX()] == '0') {
        init();
    }
}


