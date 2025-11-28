#include "Move.h"

void create_move(int x, int y, std::vector<Piece::Move>* arr, Piece* piece) {
    if (!piece->get_chessboard()->is_valid_field(x, y)) return;

    Piece* piece_on_field = piece->get_chessboard()->get_piece(x, y);
    if (piece_on_field == nullptr || (piece_on_field->colour != piece->colour)) {
        arr->push_back({x, y});
    }
}