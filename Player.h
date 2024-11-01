//
// Created by Daria Kuznetsova on 03.09.2024.
//

#ifndef MAZE_PLAYER_H
#define MAZE_PLAYER_H

#include <iostream>

class Player {
private:
    size_t x,y;
public:
    Player() = default;

    void setX(size_t x);

    void setY(size_t y);

    size_t getX() const;

    size_t getY() const;

    void setPosition(size_t newX, size_t newY);

    void moveUp();
    void moveRight();
    void moveLeft();
    void moveDown();
};


#endif //MAZE_PLAYER_H
