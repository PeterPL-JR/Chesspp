#include "../Move.h"

void create_castling(Piece* king, int rook_x, std::vector<Piece::Move>* arr) {
    Chessboard* chessboard = king->get_chessboard();
    int king_x = king->get_x();
    int king_y = king->get_y();

    Piece* rook = chessboard->get_piece(rook_x, king_y);
    if (rook != nullptr && !rook->is_moved() && !rook->is_attacked()) {
        int start_x = std::min(king_x, rook_x);
        int end_x = std::max(king_x, rook_x);

        for (int x = start_x + 1; x < end_x; x++) {
            if (chessboard->is_field_taken(x, king_y) || chessboard->is_field_attacked(x, king_y, Piece::get_opposite_colour(king->colour))) {
                return;
            }
        }

        int dir = rook_x - king_x > 0 ? 1 : -1;
        int move_x = king_x + 2 * dir;
        arr->push_back({move_x, king_y, king_x, king_y, king});
    }
}

PIECE_MOVE(king_move) {
    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            create_move(piece->get_x() + i, piece->get_y() + j, arr, piece);
        }
    }
    if (!piece->is_moved() && !piece->is_attacked()) {
        create_castling(piece, 0, arr);
        create_castling(piece, Chessboard::SIZE - 1, arr);
    }
    return arr;
}