//
// Created by Daria Kuznetsova on 22.11.2024.
//

#ifndef MAZE_DIALOGWINDOW_H
#define MAZE_DIALOGWINDOW_H

#include "iostream"
#include "Button.h"

class DialogWindow {
private:
    const char *text;
    std::vector<Button> buttons;
    const char *buttonTextRight;
    const char *buttonTextLeft;
    int screenWidth, screenHeight;
    int width = 300, height = 200;
    int x, y;
public:
    bool isActive;
    DialogWindow(const char *text, const char *buttonTextRight, const char *buttonTextLef, const std::vector<Button> &buttons, int screenWidth, int screenHeight, bool isActive);

    bool getIsActive() const;
    void activate();
    void render();

};

#endif //MAZE_DIALOGWINDOW_H