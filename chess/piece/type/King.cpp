#include "../Move.h"

PIECE_MOVE(king_move) {
    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            create_move(piece->get_x() + i, piece->get_y() + j, arr, piece);
        }
    }
    return arr;
}