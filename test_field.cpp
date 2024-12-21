//
// Created by Daria Kuznetsova on 21.12.2024.
//

#include <catch2/catch_test_macros.hpp>
#include "Field.h"
#include "iostream"

TEST_CASE("Field: Generate and validate maze", "[Field]") {
    Field field;
    field.generateField();

    SECTION("Maze dimensions are odd and within limits") {
        REQUIRE(field.getX() % 2 == 1);
        REQUIRE(field.getY() % 2 == 1);
        REQUIRE(field.getX() >= 35);
        REQUIRE(field.getY() >= 35);
        REQUIRE(field.getX() <= 96);
        REQUIRE(field.getY() <= 65);
    }

    SECTION("Start and exit positions are correctly set") {
        Coords start = field.getStartPosition();
        Coords exit = field.getExitPosition();

        REQUIRE(field.getField()[start.getY()][start.getX()] == 's');
        REQUIRE(field.getField()[exit.getY()][exit.getX()] == '0');
    }
}

TEST_CASE("Field: Find longest way", "[Field]") {
    Field field;
    SECTION("Path exists") {
        std::vector<std::vector<char>> smallMaze = {
                {'x', 'x', 'x', 'x', 'x', 'x', 'x'},
                {'x', ' ', ' ', ' ', ' ', ' ', 'x'},
                {'x', ' ', 'x', ' ', 'x', ' ', 'x'},
                {'x', ' ', 'x', ' ', 'x', ' ', 'x'},
                {'x', 'x', 'x', 'x', 'x', 'x', 'x'}
        };

        std::vector<std::vector<int>> coords = {{1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {5,2}, {5,3}};

        field.setField(smallMaze);
        field.setX(7);
        field.setY(5);
        field.setStartPosition(1, 1);
        field.setExitPosition(5, 3);

        auto longestPath = field.findLongestPath(1, 1);
        std::vector<std::pair<int, int>> longestPathCoords;
        longestPathCoords.reserve(longestPath.size());
        for (const auto& coord : longestPath) {
            longestPathCoords.emplace_back(coord.getX(), coord.getY());
        }

        REQUIRE_FALSE(longestPath.empty());
        REQUIRE(longestPath.back().getX() == 5);
        REQUIRE(longestPath.back().getY() == 3);
        REQUIRE(longestPath.size() == 7);
        REQUIRE(coords.size() == longestPath.size());
        for (size_t i = 0; i < coords.size(); ++i) {
            REQUIRE(longestPathCoords[i].first == coords[i][0]);
            REQUIRE(longestPathCoords[i].second == coords[i][1]);
        }
    }
}

TEST_CASE("Field: Get neighbours", "[Field]") {
    Field field;

    SECTION("Get neighbours for a given cell") {
        std::vector<std::vector<char>> smallMaze = {
                {'x', 'x', 'x', 'x', 'x'},
                {'x', 'x', 'x', 'x', 'x'},
                {'x', 'x', ' ', 'x', 'x'},
                {'x', 'x', 'x', 'x', 'x'},
                {'x', 'x', 'x', 'x', 'x'}
        };

        field.setField(smallMaze);
        field.setX(5);
        field.setY(5);
        field.setStartPosition(0,0);
        field.setExitPosition(0,0);

        Coords cell(2, 2);
        std::vector<Coords> neighbours = field.getNeighbours(cell);

        std::vector<Coords> expectedNeighbours = {
                Coords(2, 4),
                Coords(4, 2),
                Coords(2, 0),
                Coords(0, 2)
        };

        REQUIRE_FALSE(neighbours.empty());

        REQUIRE(neighbours.size() == expectedNeighbours.size());

        for (size_t i = 0; i < neighbours.size(); ++i) {
            REQUIRE(neighbours[i].getX() == expectedNeighbours[i].getX());
            REQUIRE(neighbours[i].getY() == expectedNeighbours[i].getY());
        }
    }

    SECTION("No neighbours if surrounded by walls") {
        std::vector<std::vector<char>> smallMaze = {
                {'x', 'x', 'x'},
                {'x', 'x', 'x'},
                {'x', 'x', 'x'}
        };

        field.setField(smallMaze);
        field.setX(3);
        field.setY(3);
        field.setStartPosition(0,0);
        field.setExitPosition(0,0);

        Coords cell(1, 1);
        std::vector<Coords> neighbours = field.getNeighbours(cell);

        REQUIRE(neighbours.empty());
    }
}