cmake_minimum_required(VERSION 3.16)
project(Chesspp)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(Chesspp main.cpp
        graphics/Window.cpp
        graphics/Window.h
        chess/Field.cpp
        chess/Field.h)

target_link_libraries(Chesspp sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
