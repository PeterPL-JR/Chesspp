#ifndef CHESSPP_CHESSBOARD_H
#define CHESSPP_CHESSBOARD_H

#include "Field.h"
#include "Piece.h"

class Chessboard {
public:
    static Field LIGHT_FIELD;
    static Field DARK_FIELD;

    static constexpr int SIZE = 8;

    Chessboard();

    void draw(int x, int y, Window* window);

    Piece* get_piece(int x, int y);
private:
    Piece* board[SIZE][SIZE] = {};
    std::vector<Piece> pieces;

    void set_piece(int x, int y, Piece* piece);

    void draw_piece(Piece& piece, int x_offset, int y_offset, Window* window);

    void init_pieces(Piece::Colour colour, int pieces_y, int pawns_y);

    void add_new_piece(Piece::Type type, Piece::Colour colour, int x, int y);

    bool is_field_valid(int x, int y);
};

#endif