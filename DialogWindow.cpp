//
// Created by Daria Kuznetsova on 22.11.2024.
//

#include "DialogWindow.h"

DialogWindow::DialogWindow(const char *text, const char *buttonTextRight, const char *buttonTextLef,
                           const std::vector<Button> &buttons, int screenWidth, int screenHeight, bool isActive)
        : text(text), buttonTextRight(buttonTextRight), buttonTextLeft(buttonTextLef), buttons(buttons),
          screenWidth(screenWidth), screenHeight(screenHeight), isActive(isActive) {
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
}

// Renders the dialog window, including its background, text, and buttons
void DialogWindow::render() {
    BeginDrawing();

    int textSize = MeasureText(text, 20);

    DrawRectangle(x, y, width, height, LIGHTGRAY);

    DrawText(text, x + ((width - textSize) / 2), (y - (height - textSize) / 2) + 20, 20, DARKGRAY);

    for (auto &button: buttons) {
        button.handleInput(GetMousePosition());
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), button.getRect())) {
                if (button.getText() == buttonTextRight) {
                    result = DialogResult::Yes;
                } else if (button.getText() == buttonTextLeft) {
                    result = DialogResult::No;
                }
            }
        }
        button.render();
    }

    EndDrawing();
}

void DialogWindow::activate() {
    isActive = true;
    result = DialogResult::None;
}

void DialogWindow::deactivate() {
    isActive = false;
}

DialogResult DialogWindow::getResult() const {
    return result;
}


