#include "Image.h"

Image::Image(sf::Texture* texture) {
    setTexture(*texture);
}

Image::Image(sf::Texture* texture, int tex_x, int tex_y, int tex_width, int tex_height, int width, int height) {
    setTexture(*texture);
    setTextureRect(sf::IntRect(tex_x, tex_y, tex_width, tex_height));
    setScale(width / tex_width, height / tex_height);
}

void Image::draw(float x, float y, Window *window) {
    setPosition(x, y);
    window->draw(this);
}

sf::Texture Image::load_texture(std::string location) {
    sf::Texture texture;
    texture.loadFromFile("img/" + location + ".png");
    return texture;
}
