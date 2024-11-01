//
// Created by Daria Kuznetsova on 01.11.2024.
//

#include "GameRender.h"

void GameRender::gameRenderInit(size_t x, size_t y) const {
    InitWindow(x, y, "Infinite Maze");
    SetTargetFPS(10);
}

void GameRender::render(const Field& field, const Player& player) const {
    BeginDrawing();
    ClearBackground(BLACK);
    renderField(field);
    renderPlayer(player);

    EndDrawing();
}

void GameRender::renderField(const Field &field) const {
    const auto& maze = field.getField();

    for (size_t y = 0; y < maze.size(); ++y) {
        for (size_t x = 0; x < maze[y].size(); ++x) {
            Color color = (maze[y][x] == 'x') ? WHITE : BLACK;
            DrawRectangle(static_cast<int>(x) * TILE_SIZE, static_cast<int>(y) * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
        }
    }
    Coords exit = field.getExitPosition();
    DrawRectangle(static_cast<int>(exit.getX()) * TILE_SIZE, static_cast<int>(exit.getY()) * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
}

void GameRender::renderPlayer(const Player &player) const {
    size_t playerX = player.getX();
    size_t playerY = player.getY();
    DrawRectangle(static_cast<int>(playerX) * TILE_SIZE, static_cast<int>(playerY) * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
}

void GameRender::close() {
    CloseWindow();
}

const int GameRender::getTileSize() const {
    return TILE_SIZE;
}
