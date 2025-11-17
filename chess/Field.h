#ifndef CHESSPP_FIELD_H
#define CHESSPP_FIELD_H

#include <SFML/Graphics.hpp>

#include "../graphics/Window.h"

class Field {
public:
    struct Type {
        sf::Color main_colour, border_colour;
    };

    const sf::Color main_colour, border_colour;

    static float size;

    Field(sf::Color main_colour, sf::Color border_colour);

    void draw(float x, float y, Window* window);
private:
    sf::RectangleShape field, border_x, border_y;
};

#endif