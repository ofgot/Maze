//
// Created by Daria Kuznetsova on 22.11.2024.
//

#include "DialogWindow.h"

DialogWindow::DialogWindow(const char *text, const char *buttonTextRight, const char *buttonTextLef, const std::vector<Button> &buttons, int screenWidth, int screenHeight, bool isActive)
    : text(text), buttonTextRight(buttonTextRight), buttonTextLeft(buttonTextLef), buttons(buttons), screenWidth(screenWidth), screenHeight(screenHeight), isActive(isActive) {
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
}

void DialogWindow::render() {
    BeginDrawing();

    int textSize = MeasureText(text, 20);

    DrawRectangle(x, y, width, height, LIGHTGRAY);

    DrawText(text, x + ((width - textSize) / 2) , y - (height - textSize) / 2 , 20, BLACK);

    for (auto& button : buttons) {
        button.render();
    }

    EndDrawing();
}

bool DialogWindow::getIsActive() const {
    return isActive;
}

void DialogWindow::activate() {
    isActive = true;
}



