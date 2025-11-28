#include "../Move.h"

PIECE_MOVE(bishop_move) {
    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>;
    create_diagonal_moves(arr, piece);
    return arr;
}

void create_diagonal_moves(std::vector<Piece::Move>* arr, Piece* piece) {
    create_move_sequence(1, 1, arr, piece);
    create_move_sequence(-1, 1, arr, piece);
    create_move_sequence(1, -1, arr, piece);
    create_move_sequence(-1, -1, arr, piece);
}