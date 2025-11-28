#ifndef CHESSPP_MOVE_H
#define CHESSPP_MOVE_H

#include "../Chessboard.h"
#include "../piece/Piece.h"

#define PIECE_MOVE(name) std::vector<Piece::Move>* (name)(Piece* piece)

PIECE_MOVE(pawn_move);
PIECE_MOVE(rook_move);
PIECE_MOVE(knight_move);
PIECE_MOVE(bishop_move);
PIECE_MOVE(queen_move);
PIECE_MOVE(king_move);

void create_move(int x, int y, std::vector<Piece::Move>* arr, Piece* piece);

void create_move_sequence(int x_offset, int y_offset, std::vector<Piece::Move>* arr, Piece* piece);

void create_straight_moves(std::vector<Piece::Move>* arr, Piece* piece);
void create_diagonal_moves(std::vector<Piece::Move>* arr, Piece* piece);

#endif