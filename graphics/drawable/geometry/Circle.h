#ifndef CHESSPP_CIRCLE_H
#define CHESSPP_CIRCLE_H

#include <SFML/Graphics.hpp>

#include "../Drawable.h"
#include "../../Window.h"

class Circle : public Drawable {
public:
    Circle(int main_colour, int border_colour, float radius_multiplier, float border_size_multiplier);

    sf::Color get_main_colour();
    sf::Color get_border_colour();

    void draw(float x, float y, Window* window);
private:
    sf::Color main_colour, border_colour;
    float radius_multiplier, border_size_multiplier;
    sf::CircleShape circle;
};

#endif