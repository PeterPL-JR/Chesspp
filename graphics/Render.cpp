#include "Render.h"

#include "Colour.h"

Field LIGHT_FIELD(0xFFE3C387, 0xFFA0895E);
Field DARK_FIELD(0xFF653318, 0xFF351C0E);

Box CLICK_BOX(0xFFABA888, 0xFF737362);
Box KING_CHECK_BOX(0xFFC75F52, 0xFF8A2816);

Circle MOVE_CIRCLE(0x36000000, 0, 0.45, 0);
Circle CAPTURE_CIRCLE(0, 0x36000000, 0.85, 0.15);

Box MOVE_BOX(0xFFFFCF50, 0xFFCB9925);
Box MOVE_OLD_POS_BOX(Colour::Transparent, 0xFFCB9925);

void draw_on_chessboard(Drawable* drawable, int x_offset, int y_offset, int x, int y, Window* window) {
    float xx = x_offset + x * Field::size;
    float yy = y_offset + y * Field::size;
    drawable->draw(xx, yy, window);
}

void draw_piece(Piece* piece, int x_offset, int y_offset, Window* window) {
    float x = piece->get_x() * Field::size + x_offset;
    float y = piece->get_y() * Field::size + y_offset;
    Piece::draw(piece->type, piece->colour, x, y, window);
}

void draw_move(Piece::Move move, int x, int y, Chessboard* chessboard, Window* window) {
    Piece* piece = chessboard->get_piece(move.x, move.y);
    Circle circle = (piece == nullptr) ? MOVE_CIRCLE : CAPTURE_CIRCLE;
    draw_on_chessboard(&circle, x, y, move.x, move.y, window);
}

void draw_clicked_piece(Piece *clicked_piece, int x, int y, Chessboard* chessboard, Window *window) {
    std::vector<Piece::Move>* moves = clicked_piece->get_moves();
    for (Piece::Move move : *moves) {
        draw_move(move, x, y, chessboard, window);
    }
    draw_on_chessboard(&CLICK_BOX, x, y, clicked_piece->get_x(), clicked_piece->get_y(), window);
}

