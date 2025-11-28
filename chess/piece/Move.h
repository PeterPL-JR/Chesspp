#ifndef CHESSPP_MOVE_H
#define CHESSPP_MOVE_H

#include "Piece.h"

#define PIECE_MOVE(name) std::vector<Piece::Move>* (name)(Piece* piece)

PIECE_MOVE(pawn_move);
PIECE_MOVE(rook_move);
PIECE_MOVE(knight_move);
PIECE_MOVE(bishop_move);
PIECE_MOVE(queen_move);
PIECE_MOVE(king_move);

#endif