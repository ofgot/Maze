//
// Created by Daria Kuznetsova on 20.11.2024.
//

#ifndef MAZE_BUTTON_H
#define MAZE_BUTTON_H


#include <raylib.h>
#include <iostream>
#include <functional>

class Button {
private:
    Rectangle rect;
    const char* text;
    int textSize;
    bool isHovered;
    Color idleColor;
    Color hoverColor;
    Color idleTextColor;
    Color hoverTextColor;
public:
    Button(const Rectangle &rect, const char *text, int textSize , bool isHovered, Color idleColor, Color hoverColor, Color idleTextColor, Color hoverTextColor);
    void render() const;
    void handleInput(Vector2 mousePosition);

    const Rectangle &getRect() const;

    const char *getText() const;
};


#endif //MAZE_BUTTON_H
