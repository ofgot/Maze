//
// Created by Daria Kuznetsova on 24.08.2024.
//

#ifndef PAC_MAN_FIELD_H
#define PAC_MAN_FIELD_H

#include <iostream>
#include <vector>
#include "Coords.h"
#include <random>

class Field {
private:
    const size_t MIN_VALUE_OF_MAZE = 35;
    const size_t MAX_VALUE_OF_X = 96; //96
    const size_t MAX_VALUE_OF_Y = 65; //65

    std::vector<std::vector<char>> field;
    size_t x, y;

    size_t start_x, start_y;
    size_t exit_x, exit_y;

    std::vector<std::pair<size_t, size_t>> directions = {
            {0,  2},
            {2,  0},
            {0,  -2},
            {-2, 0}
    };

    std::vector<std::pair<size_t, size_t>> directionsForLongPath = {
            {0,  1},
            {1,  0},
            {0,  -1},
            {-1, 0}
    };

    bool ifIsNotOutOfTheMazeAndValid(size_t x, size_t y) const;

    std::vector<Coords> getNeighbours(Coords cell) const;

    void openPath(Coords current, Coords neighbour);

public:

    void generateField();

    Field() = default;

    void draw() const;

    std::vector<Coords> findLongestPath(size_t startX, size_t startY);

    Coords getStartPosition() const;

    Coords getExitPosition() const;

    const std::vector<std::vector<char>> &getField() const;

    size_t getX() const;

    size_t getY() const;

    void setField(const std::vector<std::vector<char>> &field);

    void setStartPosition(size_t startX, size_t startY);
    void setExitPosition(size_t exitX, size_t exitY);

    void setX(size_t x);

    void setY(size_t y);
};


#endif //PAC_MAN_FIELD_H
