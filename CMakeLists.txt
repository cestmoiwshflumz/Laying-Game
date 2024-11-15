cmake_minimum_required(VERSION 3.28)
project(Laying_Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(Laying_Game main.cpp
        include/Board.h
        src/Player.cpp
        src/Board.cpp
        include/Game.h
        src/Game.cpp
        src/Tiles.cpp
        nlohmann/json.hpp)
