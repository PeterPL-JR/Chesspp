#ifndef CHESSPP_PIECE_H
#define CHESSPP_PIECE_H

#include <map>
#include <memory>

#include "../Field.h"

class Chessboard;

#include "../../graphics/drawable/Image.h"

class Piece {
public:
    enum Type {
        PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
    };
    enum Colour {
        LIGHT, DARK
    };
    struct Move : Field::Pos {
        const int old_x, old_y;
        Piece* piece;
        Piece* captured_piece;
    };

    const Type type;
    const Colour colour;

    static std::map<Type, std::map<Colour, std::unique_ptr<Image>>> IMAGES;
    static std::map<Type, std::vector<Move>* (*)(Piece*)> GET_MOVES_FUNCTIONS;

    Piece(Type type, Colour colour, int x, int y, Chessboard* chessboard);

    static void init();

    static void draw(Type type, Colour colour, float x, float y, Window* window);

    int get_x();
    int get_y();

    void move(int x, int y);

    void update_moves();

    std::vector<Move>* get_moves();

    bool is_moved();

    Chessboard* get_chessboard();

    bool is_attacked();

    static Colour get_opposite_colour(Colour colour);
private:
    int x, y;
    Image* image;
    std::vector<Move>* (*get_moves_func)(Piece*);
    std::vector<Move>* moves;
    bool moved = false;
    Chessboard* chessboard;

    static void init_piece_type(Type type, int tex_pos);
};

#endif