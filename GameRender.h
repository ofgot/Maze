//
// Created by Daria Kuznetsova on 01.11.2024.
//

#ifndef MAZE_GAMERENDER_H
#define MAZE_GAMERENDER_H
#include <iostream>
#include "raylib.h"
#include "Field.h"
#include "Player.h"

class GameRender {
private:
//    const int SCREENX = 800;
//    const int SCREENY = 600;
    size_t screenX;
    size_t screenY;
    const int TILE_SIZE = 20;
public:
    void gameRenderInit(size_t x, size_t y) const;
    void render(const Field& field, const Player& player) const;
    void renderField(const Field& field) const;
    void renderPlayer(const Player& player) const;
    void close();

    const int getTileSize() const;
};


#endif //MAZE_GAMERENDER_H
