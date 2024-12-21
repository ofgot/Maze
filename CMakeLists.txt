cmake_minimum_required(VERSION 3.28)
project(Maze)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/raylib/5.0")
find_package(raylib REQUIRED)

#test 3
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(FieldTests
        test_field.cpp
        Field.cpp
        Coords.cpp
        NumberGenerator.cpp
)
target_link_libraries(FieldTests PRIVATE Catch2::Catch2WithMain)
#

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
        SaveLoadGame.cpp
        SaveLoadGame.h
)

target_link_libraries(Maze raylib)
