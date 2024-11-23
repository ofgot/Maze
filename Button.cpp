//
// Created by Daria Kuznetsova on 20.11.2024.
//

#include "Button.h"
Button::Button(const Rectangle &rect, const char *text, int textSize, bool isHovered,
               Color idleColor, Color hoverColor, Color idleTextColor, Color hoverTextColor)
        : rect(rect), text(text), textSize(textSize), idleColor(idleColor), hoverColor(hoverColor),
          isHovered(isHovered), idleTextColor(idleTextColor), hoverTextColor(hoverTextColor) {}

void Button::handleInput(Vector2 mousePosition) {
    // I don't know why I use it.
    // Maybe because in this implementation it's possible to expand it in the future if there is something needed
    isHovered = CheckCollisionPointRec(mousePosition, rect);
}

void Button::render() const {
    Color buttonColor = isHovered ? hoverColor : idleColor;
    Color textColor = isHovered ? hoverTextColor : idleTextColor;

    DrawRectangleRec(rect, buttonColor);

    int textWidth = MeasureText(text, textSize);
    float textX = rect.x + (rect.width - static_cast<float>(textWidth)) / 2;
    float textY = rect.y + (rect.height - static_cast<float>(textSize)) / 2;

    DrawText(text, static_cast<int>(textX), static_cast<int>(textY), textSize, textColor);
}

const Rectangle &Button::getRect() const {
    return rect;
}

const char *Button::getText() const {
    return text;
}



