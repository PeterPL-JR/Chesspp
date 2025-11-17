#ifndef CHESSPP_PIECE_H
#define CHESSPP_PIECE_H

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "../graphics/Image.h"

class Piece {
public:
    enum Type {
        PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    };
    enum Colour {
        LIGHT, DARK
    };

    const Type type;
    const Colour colour;

    static std::map<Type, std::map<Colour, std::unique_ptr<Image>>> IMAGES;

    Piece(Type type, Colour colour);

    static void init();

    static void draw(Type type, Colour colour, float x, float y, Window* window);
private:
    Image* image;

    static sf::Texture TEXTURE;
    static constexpr int IMG_PIECE_SIZE = 16;

    static void init_piece_type(Type type, int tex_pos);
};

#endif