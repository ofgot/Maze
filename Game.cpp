//
// Created by Daria Kuznetsova on 03.09.2024.
//

#include <thread>
#include "Game.h"


void Game::gameInit() {
    field.generateField();
    Coords startPos = field.getStartPosition();
    player.setPosition(startPos.getX(), startPos.getY());

    int newWidth = field.getX() * render.getTileSize();
    int newHeight = field.getY() * render.getTileSize();
    SetWindowSize(newWidth, newHeight);
}

void Game::run() {
    render.gameRenderInit(field.getX() * render.getTileSize(), field.getY() * render.getTileSize());

    while (!WindowShouldClose()) {
        update();
        render.render(field, player);
    }

    render.close();
}

void Game::update() {
    inputHandler.processInput(player, field);

    if (field.getField()[player.getY()][player.getX()] == '0') {
        gameInit();
    }
}


