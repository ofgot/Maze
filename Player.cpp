//
// Created by Daria Kuznetsova on 03.09.2024.
//

#include "Player.h"
#include <iostream>

size_t Player::getX() const {
    return x;
}

size_t Player::getY() const {
    return y;
}

void Player::setX(size_t x_pos) {
    Player::x = x_pos;
}

void Player::setY(size_t y_pos) {
    Player::y = y_pos;
}

void Player::setPosition(size_t newX, size_t newY) {
    x = newX;
    y = newY;
}

void Player::moveUp() {
    setY(y - 1);
}

void Player::moveRight() {
    setX(x + 1);
}

void Player::moveLeft() {
    setX(x - 1);
}

void Player::moveDown() {
    setY(y + 1);
}
