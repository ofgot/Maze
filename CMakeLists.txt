cmake_minimum_required(VERSION 3.28)
project(Maze)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/raylib/5.0")
find_package(raylib REQUIRED)

add_executable(
        Maze main.cpp
        Field.cpp
        Coords.cpp
        Player.cpp
        Player.h
        Game.cpp
        Game.h
        NumberGenerator.cpp
        NumberGenerator.h
        InputHandler.cpp
        InputHandler.h
        GameRender.cpp
        GameRender.h
        Button.cpp
        Button.h
        MenuState.cpp
        MenuState.h
        GameState.cpp
        GameState.h
        DialogWindow.cpp
        DialogWindow.h
)

target_link_libraries(Maze raylib)
