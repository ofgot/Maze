//
// Created by Daria Kuznetsova on 24.08.2024.
//

#include "Coords.h"
#include <iostream>

Coords::Coords(size_t x, size_t y) : x(x), y(y) {}

std::pair<size_t, size_t> Coords::getXY() const {
    return std::make_pair(x, y);
}

size_t Coords::getX() const {
    return x;
}

size_t Coords::getY() const {
    return y;
}

bool Coords::operator==(const Coords &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Coords::operator!=(const Coords &rhs) const {
    return !(rhs == *this);
}
