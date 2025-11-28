#ifndef CHESSPP_BOX_H
#define CHESSPP_BOX_H

#include <SFML/Graphics.hpp>

#include "../Drawable.h"
#include "../../Window.h"

class Box : public Drawable {
public:
    Box(int main_colour, int border_colour);

    sf::Color get_main_colour();
    sf::Color get_border_colour();

    void draw(float x, float y, Window* window);
private:
    sf::Color main_colour, border_colour;
    sf::RectangleShape rect;
};

#endif