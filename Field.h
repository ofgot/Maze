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
    std::vector<std::vector<char>> field;
    int x, y;
    std::vector<std::pair<int, int>> directions = {
            {0, 2},
            {2, 0},
            {0, -2},
            {-2, 0}
    };
    static std::mt19937& getEngine();
public:
    Field(int x, int y);
    void draw();
    void generateField();
    bool ifIsNotOutOfTheMazeAndValid(int x, int y) const;
    int generateRandomNumber(int size);
    std::vector<Coords> getNeighbours(Coords cell);
    bool openPath(Coords current, Coords neighbour);
};


#endif //PAC_MAN_FIELD_H
