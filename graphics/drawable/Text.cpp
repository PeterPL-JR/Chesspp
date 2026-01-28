#include "Text.h"

sf::Font Text::FONT = load_font("font");

Text::Text(std::string text, sf::Font& font, int size) : Text(font, size) {
    set_text(text);
}

Text::Text(sf::Font& font, int size) : size(size) {
    text_sf = sf::Text();
    text_sf.setFont(font);
    text_sf.setCharacterSize(size);
    set_alignment(LEFT);
}

void Text::set_text(std::string text) {
    this->text = text;
    text_sf.setString(text);
    update_text_position();
}

std::string Text::get_text() {
    return text;
}

sf::Font Text::get_font() {
    return font;
}

int Text::get_size() {
    return size;
}

void Text::set_colour(Colour& colour) {
    text_sf.setFillColor(colour.get());
}

void Text::set_border(int size, Colour& colour) {
    text_sf.setOutlineColor(colour.get());
    text_sf.setOutlineThickness(size);
}

void Text::set_alignment(Alignment alignment) {
    this->alignment = alignment;
    update_text_position();
}

void Text::draw(float x, float y, Window *window) {
    text_sf.setPosition(x + render_offset_x, y);
    window->draw(&text_sf);
}

void Text::update_text_position() {
    if (alignment == LEFT) {
        render_offset_x = 0;
    } else {
        float text_width = text_sf.getLocalBounds().width;
        if (alignment == CENTER) {
            render_offset_x = -text_width / 2;
        }
        if (alignment == RIGHT) {
            render_offset_x = -text_width;
        }
    }
}

sf::Font Text::load_font(std::string location) {
    sf::Font font;
    font.loadFromFile("font/" + location + ".ttf");
    return font;
}
