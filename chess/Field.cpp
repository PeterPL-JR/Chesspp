#include "Field.h"

Field::Field(sf::Color main_colour, sf::Color border_colour, float size) : main_colour(main_colour), border_colour(border_colour) {
    field = sf::RectangleShape();
    border_x = sf::RectangleShape();
    border_y = sf::RectangleShape();

    field.setFillColor(main_colour);
    border_x.setFillColor(border_colour);
    border_y.setFillColor(border_colour);

    set_size(size);
}

void Field::render(float x, float y, Window *window) {
    field.setPosition(x, y);
    border_x.setPosition(x, y);
    border_y.setPosition(x, y);

    window->draw(&field);
    window->draw(&border_x);
    window->draw(&border_y);
}

float Field::get_size() {
    return size;
}

void Field::set_size(float size) {
    this->size = size;

    field.setSize(sf::Vector2f(size, size));

    float border_size = size / 16;
    border_x.setSize(sf::Vector2f(size, border_size));
    border_y.setSize(sf::Vector2f(border_size, size));
}
