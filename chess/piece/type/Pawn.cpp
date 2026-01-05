#include "../Move.h"

int get_move_offset(Piece* pawn) {
    return pawn->colour == Piece::LIGHT ? -1 : 1;
}

void create_en_passant(Piece* pawn, Piece* to_capture, std::vector<Piece::Move>* arr) {
    int x = pawn->get_x();
    int y = pawn->get_y();

    int to_capture_x = to_capture->get_x();
    int to_capture_y = to_capture->get_y();

    if (abs(x - to_capture_x) == 1 && y == to_capture_y) {
        int move_x = to_capture_x;
        int move_y = y + get_move_offset(pawn);

        Piece::Move move = {move_x, move_y, x, y, pawn, to_capture};
        arr->push_back(move);
    }
}

PIECE_MOVE(pawn_move) {
    int x = piece->get_x();
    int y = piece->get_y();

    int offset = get_move_offset(piece);
    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>();
    Chessboard* chessboard = piece->get_chessboard();

    int move_x = x;
    int move_y = y + offset;

    int capture1_x = move_x - 1;
    int capture1_y = move_y;

    int capture2_x = move_x + 1;
    int capture2_y = move_y;

    Piece* piece_to_capture1 = chessboard->get_piece(capture1_x, capture1_y);
    Piece* piece_to_capture2 = chessboard->get_piece(capture2_x, capture2_y);

    Piece::Move capture1 = {move_x - 1, move_y, x, y, piece, piece_to_capture1};
    Piece::Move capture2 = {move_x + 1, move_y, x, y, piece, piece_to_capture2};

    if (piece_to_capture1 != nullptr && piece_to_capture1->colour != piece->colour) arr->push_back(capture1);
    if (piece_to_capture2 != nullptr && piece_to_capture2->colour != piece->colour) arr->push_back(capture2);

    if (chessboard->is_field_taken(move_x, move_y)) {
        return arr;
    }

    arr->push_back({x, y + offset, x, y, piece});
    if (!piece->is_moved()) {
        move_x = x;
        move_y = y + offset * 2;
        if (chessboard->is_field_taken(move_x, move_y)) {
            return arr;
        }
        arr->push_back({move_x, move_y, x, y, piece});
    }

    Piece::Move* last_move = chessboard->get_last_move();
    if (last_move != nullptr && last_move->piece->type == Piece::PAWN && abs(last_move->y - last_move->old_y) == 2) {
        create_en_passant(piece, last_move->piece, arr);
    }
    return arr;
}