//
// Created by Daria Kuznetsova on 24.08.2024.
//

#include "Field.h"
#include "Coords.h"
#include <iostream>
#include <vector>
#include <random>
#include <stack>
using namespace std;

Field::Field(int x, int y) : x(x), y(y), field(y, std::vector<char>(x, 'x')) {}


void Field::draw() {
    for (auto & i : field) {
        for (char j : i)
            std::cout << j << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Field::generateField() {
    std::stack<Coords> cellsOfTheMaze;
    std::vector<Coords> neighbours;

    Coords start(5,5);
    field[start.getY()][start.getX()] = '.';
    cellsOfTheMaze.push(start);

    while (!cellsOfTheMaze.empty()){

        Coords current = cellsOfTheMaze.top();
        cellsOfTheMaze.pop();
        neighbours = getNeighbours(current);

        if (!neighbours.empty()){
            cellsOfTheMaze.push(current);
            int index = generateRandomNumber(neighbours.size());

            Coords neighbour = neighbours[index];

            if (openPath(current, neighbour)){
                cellsOfTheMaze.push(neighbour);
            }
        }
    }
}

bool Field::openPath(Coords current, Coords neighbour) {
    int midX = (current.getX() + neighbour.getX()) / 2;
    int midY = (current.getY() + neighbour.getY()) / 2;

    field[midY][midX] = '.';
    field[neighbour.getY()][neighbour.getX()] = '.';

    return true;
}


std::vector<Coords> Field::getNeighbours(Coords cell) {
    vector<Coords> neighbours;
    for (const auto& direction : directions) {
        int newX = cell.getX() + direction.first;
        int newY = cell.getY() + direction.second;

        if (ifIsNotOutOfTheMazeAndValid(newX, newY)){
            neighbours.emplace_back(newX, newY);
        }
    }
    return neighbours;
}

bool Field::ifIsNotOutOfTheMazeAndValid(int newX, int newY) const {
    return newX >= 0 && newX < x && newY >= 0 && newY < y && field[newY][newX] == 'x';

}

int Field::generateRandomNumber(int size) {
    std::uniform_int_distribution<> distribution(0, size - 1);
    return distribution(getEngine());
}

std::mt19937 &Field::getEngine() {
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}


