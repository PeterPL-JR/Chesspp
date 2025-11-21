#include "Field.h"
#include "../graphics/Colour.h"

float Field::size = 64;

Field::Field(int main_colour, int border_colour) : main_colour(Colour(main_colour).get()), border_colour(Colour(border_colour).get()) {
    field = sf::RectangleShape();
    border_x = sf::RectangleShape();
    border_y = sf::RectangleShape();

    field.setFillColor(this->main_colour);
    border_x.setFillColor(this->border_colour);
    border_y.setFillColor(this->border_colour);
}

void Field::draw(float x, float y, Window *window) {
    field.setSize(sf::Vector2f(size, size));

    float border_size = size / 16;
    border_x.setSize(sf::Vector2f(size, border_size));
    border_y.setSize(sf::Vector2f(border_size, size));

    field.setPosition(x, y);
    border_x.setPosition(x, y);
    border_y.setPosition(x, y);

    window->draw(&field);
    window->draw(&border_x);
    window->draw(&border_y);
}