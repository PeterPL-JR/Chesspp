#include "Colour.h"

const int Colour::Transparent = -1;

Colour::Colour(int r, int g, int b, int alpha) : r(r), g(g), b(b), alpha(alpha) {
    hex = (alpha << 24) | (r << 16) | (g << 8) | b;
    colour = sf::Color(r, g, b, alpha);
}

Colour::Colour(int r, int g, int b) : Colour(r, g, b, 255) {
}

Colour::Colour(int hex) : hex(hex) {
    alpha = (hex >> 24) & 0xff;
    r = (hex >> 16) & 0xff;
    g = (hex >> 8) & 0xff;
    b = hex & 0xff;
    colour = sf::Color(r, g, b, alpha);
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

int Colour::get_alpha() {
    return alpha;
}

int Colour::get_hex() {
    return hex;
}

sf::Color Colour::get() {
    return colour;
}
