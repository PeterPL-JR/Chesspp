#include "../Move.h"

PIECE_MOVE(rook_move) {
    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>;
    create_straight_moves(arr, piece);
    return arr;
}

void create_straight_moves(std::vector<Piece::Move>* arr, Piece* piece) {
    create_move_sequence(1, 0, arr, piece);
    create_move_sequence(-1, 0, arr, piece);
    create_move_sequence(0, 1, arr, piece);
    create_move_sequence(0, -1, arr, piece);
}