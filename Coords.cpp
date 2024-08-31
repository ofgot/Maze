//
// Created by Daria Kuznetsova on 24.08.2024.
//

#include "Coords.h"
#include <iostream>

Coords::Coords(int x, int y) : x(x), y(y) {}

std::pair<int, int> Coords::getXY() const {
    return std::make_pair(x,y);
}

int Coords::getX() const {
    return x;
}

int Coords::getY() const {
    return y;
}

bool Coords::operator==(const Coords &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Coords::operator!=(const Coords &rhs) const {
    return !(rhs == *this);
}
