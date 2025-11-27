#ifndef CHESSPP_PIECE_H
#define CHESSPP_PIECE_H

#include <map>
#include <memory>

#include "../graphics/Image.h"

class Piece {
public:
    enum Type {
        PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    };
    enum Colour {
        LIGHT, DARK
    };
    struct Move {
        const int x, y;
    };

    const Type type;
    const Colour colour;

    static std::map<Type, std::map<Colour, std::unique_ptr<Image>>> IMAGES;
    static std::map<Type, std::vector<Move>* (*)(Piece*)> GET_MOVES_FUNCTIONS;

    Piece(Type type, Colour colour, int x, int y);

    static void init();

    static void draw(Type type, Colour colour, float x, float y, Window* window);

    int get_x();
    int get_y();

    void update_moves();

    std::vector<Move>* get_moves();
private:
    int x, y;
    Image* image;
    std::vector<Move>* (*get_moves_func)(Piece*);
    std::vector<Move>* moves;

    static void init_piece_type(Type type, int tex_pos);
};

#endif