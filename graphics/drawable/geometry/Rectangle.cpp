#include "Rectangle.h"

Rectangle::Rectangle(int width, int height, Colour &colour) : width(width), height(height) {
    rect = sf::RectangleShape(sf::Vector2f(width, height));
    rect.setFillColor(colour.get());
}

int Rectangle::get_width() {
    return width;
}

int Rectangle::get_height() {
    return height;
}

void Rectangle::draw(float x, float y, Window *window) {
    rect.setPosition(x, y);
    window->draw(&rect);
}
