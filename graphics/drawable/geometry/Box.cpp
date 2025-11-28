#include "Box.h"

#include "../../Colour.h"
#include "../../../chess/Field.h"

Box::Box(int main_colour, int border_colour) {
    rect = sf::RectangleShape();

    this->main_colour = main_colour != Colour::Transparent ? Colour(main_colour).get() : sf::Color::Transparent;
    this->border_colour = border_colour != Colour::Transparent ? Colour(border_colour).get() : sf::Color::Transparent;

    rect.setFillColor(this->main_colour);
    rect.setOutlineColor(this->border_colour);
}

sf::Color Box::get_main_colour() {
    return main_colour;
}

sf::Color Box::get_border_colour() {
    return border_colour;
}

void Box::draw(float x, float y, Window *window) {
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(Field::size, Field::size));
    rect.setOutlineThickness(-Field::size / 16);
    window->draw(&rect);
}