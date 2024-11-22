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
    const float buttonWidth = 200;
    const float buttonHeight = 50;
    Color colors[3] = {RED, BLUE, BLACK };

    const int TILE_SIZE = 10;
public:
    void gameRenderInit(size_t x, size_t y) const;
    void render(const Field& field, const Player& player) const;
    void renderField(const Field& field) const;
    void renderPlayer(const Player& player) const;
    void close();
    void menuRender(float width, float height);
    void drawMovingRectangles(float width, float height);

    int getTileSize() const;

    std::vector<Button> getMenuButtons(float width, float height);

    void renderTopPanel() const;

    void drawMainText(float width, float height);

    void returnButton() const;
};


#endif //MAZE_GAMERENDER_H
