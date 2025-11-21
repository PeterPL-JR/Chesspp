#ifndef CHESSPP_COLOUR_H
#define CHESSPP_COLOUR_H

#include <SFML/Graphics.hpp>

class Colour {
public:
    Colour(int r, int g, int b);
    Colour(int hex);

    int get_r();
    int get_g();
    int get_b();

    int get_hex();

    sf::Color get();

    static const int Transparent;
private:
    int r, g, b, hex;
    sf::Color colour;
};

#endif