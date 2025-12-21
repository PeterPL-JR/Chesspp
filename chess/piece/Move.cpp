#include "Move.h"

void create_move(int x, int y, std::vector<Piece::Move>* arr, Piece* piece) {
    if (!piece->get_chessboard()->is_valid_field(x, y)) return;

    Piece* piece_on_field = piece->get_chessboard()->get_piece(x, y);
    if (piece_on_field == nullptr || (piece_on_field->colour != piece->colour)) {
        arr->push_back({x, y, piece->get_x(), piece->get_y(), piece, piece_on_field});
    }
}

void create_move_sequence(int x_offset, int y_offset, std::vector<Piece::Move>* arr, Piece* piece) {
    int x = piece->get_x();
    int y = piece->get_y();

    for (int i = 1; i < Chessboard::SIZE; i++) {
        int xx = x + i * x_offset;
        int yy = y + i * y_offset;
        create_move(xx, yy, arr, piece);
        if (piece->get_chessboard()->is_field_taken(xx, yy)) {
            return;
        }
    }
}