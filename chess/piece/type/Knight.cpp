#include "../Move.h"

PIECE_MOVE(knight_move) {
    int x = piece->get_x();
    int y = piece->get_y();

    std::vector<Piece::Move>* arr = new std::vector<Piece::Move>;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            if (i == j) continue;
            create_move(x + i, y + j, arr, piece);
            create_move(x + i, y - j, arr, piece);
            create_move(x - i, y + j, arr, piece);
            create_move(x - i, y - j, arr, piece);
        }
    }
    return arr;
}