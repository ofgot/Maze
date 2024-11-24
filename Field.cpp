//
// Created by Daria Kuznetsova on 24.08.2024.
//

#include "Field.h"
#include "Coords.h"
#include "NumberGeneration.h"
#include <iostream>
#include <vector>
#include <stack>

void Field::draw() const {
    for (const auto &i: field) {
        for (char j: i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Field::generateField() {
    x = NumberGeneration::generateRandomOddNumber(MIN_VALUE_OF_MAZE, MAX_VALUE_OF_X);
    y = NumberGeneration::generateRandomOddNumber(MIN_VALUE_OF_MAZE, MAX_VALUE_OF_Y);
    std::cout << x << " " << y << std::endl;

    field = std::vector<std::vector<char>>(y, std::vector<char>(x, 'x'));

    start_x = NumberGeneration::generateRandomOddNumber(1, x - 1);
    start_y = NumberGeneration::generateRandomOddNumber(1, y - 1);

//    std::cout << start_x << " " << start_y << std::endl;

    std::stack<Coords> cellsOfTheMaze;
    std::vector<Coords> neighbours;

    Coords start(start_x, start_y);
    field[start.getY()][start.getX()] = ' ';
    cellsOfTheMaze.push(start);

    while (!cellsOfTheMaze.empty()) {
        Coords current = cellsOfTheMaze.top();
        cellsOfTheMaze.pop();
        neighbours = getNeighbours(current);

        if (!neighbours.empty()) {
            cellsOfTheMaze.push(current);

            size_t index = NumberGeneration::generateRandomNumber(0, neighbours.size() - 1);
//            std::cout << "random number for neighbours " << index << std::endl;
//            std::cout << "size of neighbours " << neighbours.size() << std::endl;

            Coords neighbour = neighbours[index];

            openPath(current, neighbour);
            cellsOfTheMaze.push(neighbour);
        }
    }

    auto lon = findLongestPath(start_x, start_y);

//    for (auto i : lon) {
////        std::cout << i.getX() << " " << i.getY() << std::endl;
//        field[i.getY()][i.getX()] = '.';
//    }

    Coords lastCoord = lon.back();
    exit_x = lastCoord.getX();
    exit_y = lastCoord.getY();

    field[exit_y][exit_x] = '0';
    field[start_y][start_x] = 's';

//    draw();
}

void Field::openPath(const Coords current, const Coords neighbour) {
    size_t midX = (current.getX() + neighbour.getX()) / 2;
    size_t midY = (current.getY() + neighbour.getY()) / 2;

    field[midY][midX] = ' ';
    field[neighbour.getY()][neighbour.getX()] = ' ';

}

std::vector<Coords> Field::getNeighbours(const Coords cell) const {
    std::vector<Coords> neighbours;
    for (const auto &direction: directions) {
        size_t newX = cell.getX() + direction.first;
        size_t newY = cell.getY() + direction.second;

        if (ifIsNotOutOfTheMazeAndValid(newX, newY)) {
            neighbours.emplace_back(newX, newY);
        }
    }
    return neighbours;
}

bool Field::ifIsNotOutOfTheMazeAndValid(size_t newX, size_t newY) const {
    return newX < x && newY < y && field[newY][newX] == 'x';
}

const std::vector<std::vector<char>>& Field::getField() const {
    return field;
}

//void printwatever(std::vector<std::vector<bool>> visited){
//    for (const auto &i: visited) {
//        for (bool j: i) {
//            std::cout << j << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//}

std::vector<Coords> Field::findLongestPath(size_t startX, size_t startY) {
    std::stack<std::pair<Coords, std::vector<Coords>>> stack;
    std::vector<std::vector<bool>> visited(y, std::vector<bool>(x, false));

    size_t longest = 0;
    std::vector<Coords> longestPath;

    stack.emplace(Coords(startX, startY), std::vector<Coords>{Coords(startX, startY)});

    while (!stack.empty()) {
        auto top = stack.top();
        stack.pop();

        Coords currentCoord = top.first;
        std::vector<Coords> currentPath = top.second;

        if (currentPath.size() > longest) {
            longest = currentPath.size();
            longestPath = currentPath;
        }

        visited[currentCoord.getY()][currentCoord.getX()] = true;
//        printwatever(visited);

        for (const auto &dir : directionsForLongPath) {
            size_t newX = currentCoord.getX() + dir.first;
            size_t newY = currentCoord.getY() + dir.second;

//            printwatever(visited);

            if (field[newY][newX] == ' ' && !visited[newY][newX]) {
                std::vector<Coords> newPath = currentPath;
                newPath.emplace_back(newX, newY);
                stack.push(std::make_pair(Coords(newX, newY), newPath));
//                printwatever(visited);
            }
        }
    }
    return longestPath;
}

Coords Field::getStartPosition() const {
    return {start_x, start_y};
}

Coords Field::getExitPosition() const {
    return {exit_x, exit_y};
}

size_t Field::getX() const {
    return x;
}

size_t Field::getY() const {
    return y;
}

void Field::setField(const std::vector<std::vector<char>> &field) {
    Field::field = field;
}

void Field::setStartPosition(size_t startX, size_t startY) {
    start_x = startX;
    start_y = startY;
}

void Field::setExitPosition(size_t exitX, size_t exitY) {
    exit_x = exitX;
    exit_y = exitY;
}

void Field::setX(size_t x) {
    Field::x = x;
}

void Field::setY(size_t y) {
    Field::y = y;
}

