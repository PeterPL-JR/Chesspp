#ifndef CHESSPP_IMAGE_H
#define CHESSPP_IMAGE_H

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "../Window.h"

class Image : public sf::Sprite, public Drawable {
public:
    Image(sf::Texture* texture);
    Image(sf::Texture* texture, int tex_x, int tex_y, int tex_width, int tex_height, int width, int height);

    void draw(float x, float y, Window* window);

    static sf::Texture load_texture(std::string location);
};

#endif