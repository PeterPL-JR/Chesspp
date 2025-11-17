#ifndef CHESSPP_CHESSBOARD_H
#define CHESSPP_CHESSBOARD_H

#include "Field.h"

class Chessboard {
public:
    static Field LIGHT_FIELD;
    static Field DARK_FIELD;

    static constexpr int SIZE = 8;

    void draw(int x, int y, Window* window);
};

#endif