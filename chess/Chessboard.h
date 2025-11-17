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

private:
    std::vector<Piece> pieces;

    void draw_piece(Piece& piece, int x_offset, int y_offset, Window* window);

    void init_pieces(Piece::Colour colour, int pieces_y, int pawns_y);
};

#endif