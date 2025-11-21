#include "Colour.h"

Colour::Colour(int r, int g, int b) : r(r), g(g), b(b) {
    hex = (r << 16) | (g << 8) | b;
    colour = sf::Color(r, g, b);
}

Colour::Colour(int hex) : hex(hex) {
    r = (hex >> 16) & 0xff;
    g = (hex >> 8) & 0xff;
    b = hex & 0xff;
    colour = sf::Color(r, g, b);
}

int Colour::get_r() {
    return r;
}

int Colour::get_g() {
    return g;
}

int Colour::get_b() {
    return b;
}

int Colour::get_hex() {
    return hex;
}

sf::Color Colour::get() {
    return colour;
}
