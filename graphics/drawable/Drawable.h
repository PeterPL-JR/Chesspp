#ifndef CHESSPP_DRAWABLE_H
#define CHESSPP_DRAWABLE_H

#include "../Window.h"

class Drawable {
public:
    virtual ~Drawable() = default;

    virtual void draw(float x, float y, Window* window) = 0;
};

#endif