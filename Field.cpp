//
// Created by Daria Kuznetsova on 24.08.2024.
//

#include "Field.h"
#include "Coords.h"
#include "NumberGenerator.h"
#include <iostream>
#include <vector>
#include <stack>

// Draws the current state of the maze to the console.
void Field::draw() const {
    for (const auto &i: field) {
        for (char j: i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Generates a random maze using depth-first search algorithm (DFS) with a start ('s') and an exit ('0') point.
void Field::generateField() {
    // Generate random odd dimensions for the maze.
    x = NumberGenerator::generateRandomOddNumber(MIN_VALUE_OF_MAZE, MAX_VALUE_OF_X);
    y = NumberGenerator::generateRandomOddNumber(MIN_VALUE_OF_MAZE, MAX_VALUE_OF_Y);
    std::cout << x << " " << y << std::endl;

    // Initialize the maze grid with walls ('x').
    field = std::vector<std::vector<char>>(y, std::vector<char>(x, 'x'));

    // Generate random start coordinates within the maze.
    start_x = NumberGenerator::generateRandomOddNumber(1, x - 1);
    start_y = NumberGenerator::generateRandomOddNumber(1, y - 1);

    // Stack for backtracking and a list for storing valid neighbors.
    std::stack<Coords> cellsOfTheMaze;
    std::vector<Coords> neighbours;

    // Set the starting cell as open and push it to the stack.
    Coords start(start_x, start_y);
    field[start.getY()][start.getX()] = ' ';
    cellsOfTheMaze.push(start);

    // Generate the maze using a randomized depth-first search algorithm(DFS).
    while (!cellsOfTheMaze.empty()) {
        Coords current = cellsOfTheMaze.top();
        cellsOfTheMaze.pop();
        neighbours = getNeighbours(current);

        if (!neighbours.empty()) {
            // Push the current cell back and select a random neighbor.
            cellsOfTheMaze.push(current);

            size_t index = NumberGenerator::generateRandomNumber(0, neighbours.size() - 1);

            Coords neighbour = neighbours[index];

            // Open a path between the current cell and the neighbor.
            openPath(current, neighbour);
            cellsOfTheMaze.push(neighbour);
        }
    }

    // Find the longest path in the maze and set the exit point.
    auto lon = findLongestPath(start_x, start_y);
    Coords lastCoord = lon.back();
    exit_x = lastCoord.getX();
    exit_y = lastCoord.getY();

    field[exit_y][exit_x] = '0'; // Exit point.
    field[start_y][start_x] = 's'; // Start point.

}

// Opens a path between the current cell and its neighbor.
void Field::openPath(const Coords current, const Coords neighbour) {
    size_t midX = (current.getX() + neighbour.getX()) / 2;
    size_t midY = (current.getY() + neighbour.getY()) / 2;

    field[midY][midX] = ' ';
    field[neighbour.getY()][neighbour.getX()] = ' ';

}

// Returns a list of all valid neighbors of the given cell.
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

// Checks if the cell is within the maze boundaries and still a wall ('x').
bool Field::ifIsNotOutOfTheMazeAndValid(size_t newX, size_t newY) const {
    return newX < x && newY < y && field[newY][newX] == 'x';
}

// Returns the maze grid as a 2D vector.
const std::vector<std::vector<char>> &Field::getField() const {
    return field;
}

// Finds the longest path from a given starting position using DFS.
std::vector<Coords> Field::findLongestPath(size_t startX, size_t startY) {
    std::stack<std::pair<Coords, std::vector<Coords>>> stack;
    std::vector<std::vector<bool>> visited(y, std::vector<bool>(x, false));

    size_t longest = 0;
    std::vector<Coords> longestPath;

    // Push the starting position to the stack with an initial path.
    stack.emplace(Coords(startX, startY), std::vector<Coords>{Coords(startX, startY)});

    while (!stack.empty()) {
        auto top = stack.top();
        stack.pop();

        Coords currentCoord = top.first;
        std::vector<Coords> currentPath = top.second;

        // Update the longest path if the current path is longer.
        if (currentPath.size() > longest) {
            longest = currentPath.size();
            longestPath = currentPath;
        }

        visited[currentCoord.getY()][currentCoord.getX()] = true;

        // Check all valid neighboring cells.
        for (const auto &dir: directionsForLongPath) {
            size_t newX = currentCoord.getX() + dir.first;
            size_t newY = currentCoord.getY() + dir.second;

            if (field[newY][newX] == ' ' && !visited[newY][newX]) {
                std::vector<Coords> newPath = currentPath;
                newPath.emplace_back(newX, newY);
                stack.push(std::make_pair(Coords(newX, newY), newPath));
            }
        }
    }
    return longestPath;
}

// Returns the start position as a Coords object.
Coords Field::getStartPosition() const {
    return {start_x, start_y};
}

// Returns the exit position as a Coords object.
Coords Field::getExitPosition() const {
    return {exit_x, exit_y};
}

size_t Field::getX() const {return x;}

size_t Field::getY() const {return y;}

// Sets the maze grid to the given 2D vector.
void Field::setField(const std::vector<std::vector<char>> &field) {
    Field::field = field;
}

// Sets start position of the maze
void Field::setStartPosition(size_t startX, size_t startY) {
    start_x = startX;
    start_y = startY;
}

// Sets exit position of the maze
void Field::setExitPosition(size_t exitX, size_t exitY) {
    exit_x = exitX;
    exit_y = exitY;
}

void Field::setX(size_t x) {Field::x = x;}

void Field::setY(size_t y) {Field::y = y;}

