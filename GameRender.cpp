//
// Created by Daria Kuznetsova on 01.11.2024.
//

#include "GameRender.h"
#include "NumberGeneration.h"
#include "Button.h"

void GameRender::gameRenderInit(size_t x, size_t y) const {
    InitWindow(static_cast<int>(x), static_cast<int>(y), "Infinite Maze");
    SetTargetFPS(25);
}

void GameRender::render(const Field& field, const Player& player, const Button& button) const {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    renderTopPanel(button);

    renderField(field);
    renderPlayer(player);

    EndDrawing();
}

void GameRender::renderTopPanel(const Button& button) const {
    returnButton(button);
}

void GameRender::returnButton(const Button& button) const{
//    Button backButton({ 5, 10, 100, 25 }, "Back to menu", 15, false, LIGHTGRAY, GRAY);
    button.render();
}

void GameRender::renderField(const Field &field) const {
    const auto& maze = field.getField();

    for (size_t y = 0; y < maze.size(); ++y) {
        for (size_t x = 0; x < maze[y].size(); ++x) {
            Color color = (maze[y][x] == 'x') ? DARKGRAY : WHITE;
            DrawRectangle(static_cast<int>(x) * TILE_SIZE, static_cast<int>(y) * TILE_SIZE + 40, TILE_SIZE, TILE_SIZE, color);
        }
    }
    Coords exit = field.getExitPosition();
    DrawRectangle(static_cast<int>(exit.getX()) * TILE_SIZE, static_cast<int>(exit.getY()) * TILE_SIZE + 40, TILE_SIZE, TILE_SIZE, BLUE);
}

void GameRender::renderPlayer(const Player &player) const {
    size_t playerX = player.getX();
    size_t playerY = player.getY();
    DrawRectangle(static_cast<int>(playerX) * TILE_SIZE, static_cast<int>(playerY) * TILE_SIZE + 40, TILE_SIZE, TILE_SIZE, RED);
}

void GameRender::close() {
    CloseWindow();
}

int GameRender::getTileSize() const {
    return TILE_SIZE;
}

void GameRender::drawMainText(float width, float height){
    const char *text = "Infinite Maze";

    int font = 60;
    int x = (width - MeasureText(text, font)) / 2;
    int y = height / 8;

    DrawText(text, x + 3, y, font, GRAY);
    DrawText(text, x, y, font, DARKGRAY);

}

void GameRender::menuRender(float width, float height, std::vector<Button>& buttons) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    drawMovingRectangles(width, height);

    drawMainText(width, height);

    for (auto& button : buttons) {
        button.render();
    }

    EndDrawing();
}

void GameRender::drawMovingRectangles(float width, float height) {

    static float pointX[15];
    static float pointY[15];
    static float pointSpeedX[15];
    static float pointSpeedY[15];

    // init of rectangles
    static bool initialized = false;
    if (!initialized) {
        for (int i = 0; i < 15; i++) {
            // random position and speed
            pointX[i] = NumberGeneration::generateRandomNumber(0, width - 10);
            pointY[i] = NumberGeneration::generateRandomNumber(0, height - 10);

            pointSpeedX[i] = NumberGeneration::generateRandomNumber(1, 4);
            pointSpeedY[i] = NumberGeneration::generateRandomNumber(1, 4);
        }
        initialized = true;
    }

    // update rectangles position
    for (int i = 0; i < 15; i++) {
        pointX[i] += pointSpeedX[i];
        pointY[i] -= pointSpeedY[i];

        // check collision
        if (pointX[i] > width - 10 || pointX[i] < 0) pointSpeedX[i] = -pointSpeedX[i];
        if (pointY[i] > height - 10 || pointY[i] < 0) pointSpeedY[i] = -pointSpeedY[i];

        // draw rectangles
        Color currentColor = colors[i % (sizeof(colors) / sizeof(colors[0]))];

        DrawRectangle(pointX[i], pointY[i], 10, 10, currentColor);
    }
}

