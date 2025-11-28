#ifndef CHESSPP_CHESSBOARD_H
#define CHESSPP_CHESSBOARD_H

#include "Field.h"
#include "Piece.h"

#include "../graphics/Box.h"

class Chessboard {
public:
    static constexpr int SIZE = 8;

    Chessboard();

    void draw(int x, int y, Window* window);

    void click(int x, int y);

    Piece* get_piece(int x, int y);

    Piece::Colour get_turn();
    void change_turn();

    void move_piece(Piece* piece, int x, int y);
    void remove_piece(Piece* piece);

    bool is_field_taken(int x, int y);
private:
    Piece* board[SIZE][SIZE] = {};
    std::vector<Piece*> pieces;
    Piece::Colour turn = Piece::LIGHT;

    Piece* clicked_piece = nullptr;

    Field::Pos* last_move_new_pos = nullptr;
    Field::Pos* last_move_old_pos = nullptr;

    void set_piece(int x, int y, Piece* piece);

    void init_pieces(Piece::Colour colour, int pieces_y, int pawns_y);

    void update_pieces();

    void add_new_piece(Piece::Type type, Piece::Colour colour, int x, int y);

    void try_move_piece(Piece* piece, int x, int y);

    bool is_field_valid(int x, int y);
};

#endif