cmake_minimum_required(VERSION 3.28)
project(Maze)

set(CMAKE_CXX_STANDARD 14)

find_package(raylib REQUIRED)

add_executable(
        Maze main.cpp
        Field.cpp
        Coords.cpp
        Player.cpp
        Player.h
        Game.cpp
        Game.h
        NumberGeneration.cpp
        NumberGeneration.h
        InputHandler.cpp
        InputHandler.h
        GameRender.cpp
        GameRender.h
)

target_link_libraries(Maze raylib)
