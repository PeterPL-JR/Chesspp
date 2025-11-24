#include "Circle.h"

#include "Colour.h"
#include "../chess/Field.h"

Circle::Circle(int main_colour, int border_colour, float radius_multiplier, float border_size_multiplier) {
    circle = sf::CircleShape();

    this->main_colour = main_colour != Colour::Transparent ? Colour(main_colour).get() : sf::Color::Transparent;
    this->border_colour = border_colour != Colour::Transparent ? Colour(border_colour).get() : sf::Color::Transparent;

    this->radius_multiplier = radius_multiplier;
    this->border_size_multiplier = border_size_multiplier;

    circle.setFillColor(this->main_colour);
    circle.setOutlineColor(this->border_colour);
}

sf::Color Circle::get_main_colour() {
    return main_colour;
}

sf::Color Circle::get_border_colour() {
    return border_colour;
}

void Circle::draw(float x, float y, Window *window) {
    float size = Field::size * radius_multiplier;

    float xx = x + Field::size / 2 - size / 2;
    float yy = y + Field::size / 2 - size / 2;

    circle.setPosition(xx, yy);
    circle.setRadius(size / 2);
    circle.setOutlineThickness(-size * border_size_multiplier / 2);
    window->draw(&circle);
}

