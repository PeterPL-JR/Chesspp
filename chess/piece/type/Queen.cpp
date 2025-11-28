#include "../Move.h"

PIECE_MOVE(queen_move) {
    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>;
    create_straight_moves(arr, piece);
    create_diagonal_moves(arr, piece);
    return arr;
}