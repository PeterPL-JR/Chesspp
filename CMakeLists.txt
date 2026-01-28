cmake_minimum_required(VERSION 3.16)
project(Chesspp)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(Chesspp main.cpp
        graphics/Window.cpp
        graphics/Window.h
        chess/Field.cpp
        chess/Field.h
        chess/Chessboard.cpp
        chess/Chessboard.h
        chess/piece/Piece.cpp
        chess/piece/Piece.h
        graphics/drawable/Image.cpp
        graphics/drawable/Image.h
        graphics/Colour.h
        graphics/Colour.cpp
        graphics/drawable/geometry/Box.cpp
        graphics/drawable/geometry/Box.h
        graphics/drawable/geometry/Circle.cpp
        graphics/drawable/geometry/Circle.h
        chess/piece/Move.cpp
        chess/piece/Move.h
        graphics/drawable/Drawable.h
        graphics/Render.cpp
        graphics/Render.h
        chess/piece/type/Pawn.cpp
        chess/piece/type/Knight.cpp
        chess/piece/type/Bishop.cpp
        chess/piece/type/Rook.cpp
        chess/piece/type/Queen.cpp
        chess/piece/type/King.cpp
        graphics/drawable/Text.cpp
        graphics/drawable/Text.h
        graphics/drawable/geometry/Rectangle.cpp
        graphics/drawable/geometry/Rectangle.h
)

target_link_libraries(Chesspp sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
