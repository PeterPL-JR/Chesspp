#ifndef CHESSPP_FIELD_H
#define CHESSPP_FIELD_H

#include <SFML/Graphics.hpp>

#include "../graphics/Colour.h"
#include "../graphics/Window.h"

class Field {
public:
    struct Pos {
        const int x, y;
    };
    enum ColourType {
        LIGHT, DARK
    };

    static float size;

    Field(Colour& main_colour, Colour& border_colour);

    void draw(float x, float y, Window* window);
private:
    sf::RectangleShape field, border_x, border_y;
};

#endif