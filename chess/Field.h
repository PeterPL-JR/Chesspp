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

    Field(sf::Color main_colour, sf::Color border_colour, float size);

    void render(float x, float y, Window* window);

    float get_size();
    void set_size(float size);
private:
    float size;
    sf::RectangleShape field, border_x, border_y;
};

#endif