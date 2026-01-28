#ifndef CHESSPP_TEXT_H
#define CHESSPP_TEXT_H

#include <SFML/Graphics/Font.hpp>

#include "Drawable.h"
#include "../Colour.h"

class Text : public Drawable {
public:
    static sf::Font FONT;

    enum Alignment {
        LEFT, CENTER, RIGHT
    };

    Text(std::string text, sf::Font& font, int size);
    Text(sf::Font& font, int size);

    void set_text(std::string text);
    std::string get_text();

    sf::Font get_font();
    int get_size();

    void set_colour(Colour& colour);
    void set_border(int size, Colour& colour);
    void set_alignment(Alignment alignment);

    void draw(float x, float y, Window* window);

    static sf::Font load_font(std::string location);
private:
    std::string text;
    sf::Font font;
    int size;
    Alignment alignment;

    sf::Text text_sf;
    float render_offset_x = 0;

    void update_text_position();
};

#endif