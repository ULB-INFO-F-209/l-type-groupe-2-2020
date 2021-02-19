cmake_minimum_required(VERSION 3.17)
project(jeu)

set(CMAKE_CXX_STANDARD 17)

add_executable(jeu src/main.cpp src/game.cpp src/MapHandler.cpp src/MapHandler.hpp src/Player.hpp src/Player.cpp src/Interface.cpp src/Interface.hpp src/InputHandler.cpp src/InputHandler.h)