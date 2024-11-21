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

void GameRender::renderTopPanel(float width, float height) const {
    // Рендерим панель сверху
    Color panelColor = LIGHTGRAY;
    DrawRectangle(0, 0, width, 50, panelColor); // Панель сверху

    // Кнопка выхода в меню
    float buttonWidth = 100;
    float buttonHeight = 30;
    float buttonX = 10;  // Отступ от левого края
    float buttonY = 10;  // Отступ от верхнего края

    // Отображаем кнопку
    Color buttonColor = CheckCollisionPointRec(GetMousePosition(), {buttonX, buttonY, buttonWidth, buttonHeight}) ? DARKGRAY : LIGHTGRAY;
    Color textColor = (buttonColor == DARKGRAY) ? WHITE : BLACK;

    DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, buttonColor);
    DrawText("Back to Menu", buttonX + 10, buttonY + 5, 20, textColor);
}

void GameRender::render(const Field& field, const Player& player) const {
    BeginDrawing();
    ClearBackground(BLACK);

    renderTopPanel(GetScreenWidth(), GetScreenHeight());

    renderField(field);
    renderPlayer(player);

    EndDrawing();
}

void GameRender::renderField(const Field &field) const {
    const auto& maze = field.getField();

    for (size_t y = 0; y < maze.size(); ++y) {
        for (size_t x = 0; x < maze[y].size(); ++x) {
            Color color = (maze[y][x] == 'x') ? DARKGRAY : WHITE;
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

int GameRender::getTileSize() const {
    return TILE_SIZE;
}

void GameRender::menuRender(float width, float height) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    drawMovingRectangles(width, height);

    const char *text = "Infinite Maze";

    int font = 60;
    int x = (width - MeasureText(text, font)) / 2;
    int y = height / 8;

    DrawText(text, x + 3, y, font, GRAY);
    DrawText(text, x, y, font, DARKGRAY);

    auto buttons = getMenuButtons(width, height);

    for (auto& button : buttons) {
        button.isHovered = CheckCollisionPointRec(GetMousePosition(), button.rect);
        Color buttonColor = button.isHovered ? DARKGRAY : LIGHTGRAY;
        Color textColor = button.isHovered ? WHITE : BLACK;

        DrawRectangleRec(button.rect, buttonColor);

        int textWidth = MeasureText(button.text, 20);
        float textX = button.rect.x + (button.rect.width - textWidth) / 2;
        float textY = button.rect.y + (button.rect.height - 20) / 2;

        DrawText(button.text, textX, textY, 20, textColor);
    }

    EndDrawing();
}

std::vector<Button> GameRender::getMenuButtons(float width, float height) {
    std::vector<Button> buttons;

    float startButtonX = (width - buttonWidth) / 2;
    float loadButtonX = (width - buttonWidth) / 2;
    float quitButtonX = (width - buttonWidth) / 2;

    float startButtonY = (height - (buttonHeight * 3)) / 2;
    float loadButtonY = startButtonY + buttonHeight + 20;
    float quitButtonY = loadButtonY + buttonHeight + 20;

    buttons.push_back({ { startButtonX, startButtonY, buttonWidth, buttonHeight }, "Start Game", false });
    buttons.push_back({ { loadButtonX, loadButtonY, buttonWidth, buttonHeight }, "Load Game", false });
    buttons.push_back({ { quitButtonX, quitButtonY, buttonWidth, buttonHeight }, "Exit", false });

    return buttons;
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

