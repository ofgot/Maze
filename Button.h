//
// Created by Daria Kuznetsova on 20.11.2024.
//

#ifndef MAZE_BUTTON_H
#define MAZE_BUTTON_H


#include <raylib.h>

class Button {
public:
    Rectangle rect;
    const char* text;
    bool isHovered;
    Button(const Rectangle &rect, const char *text, bool isHovered);
};


#endif //MAZE_BUTTON_H
