cmake_minimum_required(VERSION 3.14)
project(main)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp src/game_controller.cpp src/game_unit.cpp src/state.cpp src/user.cpp src/player.cpp src/game_ai.cpp )