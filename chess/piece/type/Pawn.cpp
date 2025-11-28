#include "../Move.h"

PIECE_MOVE(pawn_move) {
    int x = piece->get_x();
    int y = piece->get_y();

    int offset = piece->colour == Piece::LIGHT ? -1 : 1;
    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>();
    Chessboard* chessboard = piece->get_chessboard();

    int move_x = x;
    int move_y = y + offset;

    Piece::Move capture1 = {move_x - 1, move_y};
    Piece::Move capture2 = {move_x + 1, move_y};

    Piece* piece_to_capture1 = chessboard->get_piece(capture1.x, capture1.y);
    Piece* piece_to_capture2 = chessboard->get_piece(capture2.x, capture2.y);

    if (piece_to_capture1 != nullptr && piece_to_capture1->colour != piece->colour) arr->push_back(capture1);
    if (piece_to_capture2 != nullptr && piece_to_capture2->colour != piece->colour) arr->push_back(capture2);

    if (chessboard->is_field_taken(move_x, move_y)) {
        return arr;
    }

    arr->push_back({x, y + offset});
    if (!piece->is_moved()) {
        move_x = x;
        move_y = y + offset * 2;
        if (chessboard->is_field_taken(move_x, move_y)) {
            return arr;
        }
        arr->push_back({move_x, move_y});
    }
    return arr;
}