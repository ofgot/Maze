//
// Created by Daria Kuznetsova on 01.11.2024.
//

#ifndef MAZE_GAMERENDER_H
#define MAZE_GAMERENDER_H
#include <iostream>
#include "raylib.h"
#include "Field.h"
#include "Player.h"
#include "Button.h"

class GameRender {
private:
    Color colors[3] = {RED, BLUE, BLACK };
    const int TILE_SIZE = 10;

public:
    void gameRenderInit(size_t x, size_t y) const;
    void render(const Field& field, const Player& player, const Button& backButton) const;
    void renderField(const Field& field) const;
    void renderPlayer(const Player& player) const;
    void menuRender(float width, float height, std::vector<Button>& buttons);
    void drawMovingRectangles(float width, float height);

    int getTileSize() const;

    void renderTopPanel(const Button& backButton) const;

    void drawMainText(float width, float height);

    void returnButton(const Button& button) const;
};


#endif //MAZE_GAMERENDER_H
