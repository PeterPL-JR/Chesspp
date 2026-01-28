#ifndef CHESSPP_CHESSBOARD_H
#define CHESSPP_CHESSBOARD_H

#include "Field.h"
#include "piece/Piece.h"

#include "../graphics/drawable/geometry/Box.h"

class Chessboard {
public:
    static constexpr int SIZE = 8;

    Chessboard();

    void draw(int x, int y, Window* window);

    void click(int x, int y);

    Piece* get_piece(int x, int y);
    std::vector<Piece*>& get_pieces();

    Piece::Colour get_turn();
    void change_turn();

    void do_move(Piece::Move move);
    void remove_piece(Piece* piece);

    bool is_field_taken(int x, int y);

    bool is_field_attacked(int x, int y, Piece::Colour attacked_by_colour);

    bool is_valid_field(int x, int y);

    Piece::Move* get_last_move();

    bool is_game();
private:
    Piece* board[SIZE][SIZE] = {};
    std::vector<Piece*> pieces;
    Piece::Colour turn = Piece::LIGHT;
    bool is_check = false, is_check_mate = false, is_game_end = false;
    std::vector<Piece::Move> moves;

    Piece* clicked_piece = nullptr;

    Field::Pos* last_move_new_pos = nullptr;
    Field::Pos* last_move_old_pos = nullptr;

    void set_piece(int x, int y, Piece* piece);

    std::vector<Piece*> get_pieces(Piece::Colour colour, Piece::Type type);
    bool piece_exists(Piece::Colour colour, Piece::Type type);
    bool piece_exists(Piece::Type type);

    void init_pieces(Piece::Colour colour, int pieces_y, int pawns_y);

    Field::ColourType get_field_colour(int x, int y);
    Field::ColourType get_field_colour(Piece* piece);

    void create_moves();
    void create_buffer_moves();

    void add_new_piece(Piece::Type type, Piece::Colour colour, int x, int y);

    void add_piece_to_list(Piece* piece);
    void remove_piece_from_list(Piece* piece);

    void clear_field(int x, int y);

    void try_move_piece(Piece* piece, int x, int y);

    Piece* get_king(Piece::Colour colour);
    bool is_king_attacked(Piece::Colour colour);

    void check_king_check();

    bool is_move_valid(Piece::Move move);

    bool is_pawn_promotion(Piece* piece, int y);

    void do_castling(int x, int y, int old_x);
    bool is_castling(Piece* piece, int new_x, int old_x);

    bool check_game_end();
    void game_end();

    void victory(Piece::Colour colour);
    void draw();

    bool is_king_check_mate(Piece::Colour winner);
    bool is_draw();
};

#endif