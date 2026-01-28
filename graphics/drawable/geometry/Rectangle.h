#ifndef CHESSPP_RECTANGLE_H
#define CHESSPP_RECTANGLE_H

#include "../Drawable.h"
#include "../../Colour.h"

class Rectangle : public Drawable {
public:
    Rectangle(int width, int height, Colour& colour);

    int get_width();
    int get_height();

    void draw(float x, float y, Window *window);
private:
    int width, height;
    sf::RectangleShape rect;
};

#endif