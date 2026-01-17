#include "Chessboard.h"
#include "../graphics/Colour.h"
#include "../graphics/Render.h"

const Piece::Type PIECES_ORDER[8] = {
    Piece::ROOK,
    Piece::KNIGHT,
    Piece::BISHOP,
    Piece::QUEEN,
    Piece::KING,
    Piece::BISHOP,
    Piece::KNIGHT,
    Piece::ROOK
};

Chessboard::Chessboard() {
    init_pieces(Piece::LIGHT, SIZE - 1, SIZE - 2);
    init_pieces(Piece::DARK, 0, 1);
}

void Chessboard::draw(int x, int y, Window* window) {
    for (int i = 0; i < SIZE; i++) {
        float xx = x + i * Field::size;
        for (int j = 0; j < SIZE; j++) {
            float yy = y + j * Field::size;

            Field field = get_field_colour(i, j) == Field::LIGHT ? LIGHT_FIELD : DARK_FIELD;
            field.draw(xx, yy, window);
        }
    }

    if (last_move_new_pos != nullptr) {
        draw_on_chessboard(&MOVE_BOX, x, y, last_move_new_pos->x, last_move_new_pos->y, window);
    }

    if (last_move_old_pos != nullptr) {
        draw_on_chessboard(&MOVE_OLD_POS_BOX, x, y, last_move_old_pos->x, last_move_old_pos->y, window);
    }

    if (is_check || is_check_mate) {
        Piece* king = get_king(turn);
        draw_on_chessboard(&KING_CHECK_BOX, x, y, king->get_x(), king->get_y(), window);
    }

    if (clicked_piece != nullptr) {
        draw_clicked_piece(clicked_piece, x, y, window);
    }

    for (Piece* piece : pieces) {
        draw_piece(piece, x, y, window);
    }
}

void Chessboard::click(int x, int y) {
    if (is_game_end || !(x >= 0 && y >= 0)) return;

    int field_xi = x / Field::size;
    int field_yi = y / Field::size;

    if (!(field_xi < SIZE && field_yi < SIZE)) return;

    Piece* piece = get_piece(field_xi, field_yi);

    if (clicked_piece != nullptr && (piece == nullptr || piece->colour != clicked_piece->colour)) {
        try_move_piece(clicked_piece, field_xi, field_yi);
        return;
    }

    if (clicked_piece == piece) {
        clicked_piece = nullptr;
        return;
    }

    if (piece != nullptr && piece->colour == turn) {
        clicked_piece = piece;
    }
}

Piece* Chessboard::get_piece(int x, int y) {
    if (!is_valid_field(x, y)) return nullptr;
    return board[x][y];
}

std::vector<Piece*>& Chessboard::get_pieces() {
    return pieces;
}

Piece::Colour Chessboard::get_turn() {
    return turn;
}

void Chessboard::change_turn() {
    turn = Piece::get_opposite_colour(turn);
    create_moves();
    is_check = false;

    if (check_game_end()) {
        game_end();
    } else {
        check_king_check();
    }
}

void Chessboard::do_move(Piece::Move move) {
    Piece* piece = move.piece;
    int x = move.x;
    int y = move.y;

    int old_x = move.old_x;
    int old_y = move.old_y;

    if (!is_valid_field(x, y)) return;

    Piece* to_capture = move.captured_piece;
    if (to_capture != nullptr) {
        remove_piece(to_capture);
    }

    set_piece(x, y, piece);

    piece->move(x, y);
    moves.push_back(move);

    if (is_pawn_promotion(piece, y)) {
        Piece::Colour colour = piece->colour;
        remove_piece(piece);
        add_new_piece(Piece::QUEEN, colour, x, y);
    }

    if (is_castling(piece, x, old_x)) {
        do_castling(x, y, old_x);
    }

    last_move_new_pos = new Field::Pos{x, y};
    last_move_old_pos = new Field::Pos{old_x, old_y};
}

void Chessboard::remove_piece(Piece *piece) {
    clear_field(piece->get_x(), piece->get_y());
    remove_piece_from_list(piece);
    delete piece;
}

bool Chessboard::is_field_taken(int x, int y) {
    return board[x][y] != nullptr;
}

bool Chessboard::is_field_attacked(int x, int y, Piece::Colour attacked_by_colour) {
    for (Piece* piece : pieces) {
        if (piece->colour == attacked_by_colour) {
            for (Piece::Move move : *piece->get_moves()) {
                if (move.x == x && move.y == y) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Chessboard::is_valid_field(int x, int y) {
    return x >= 0 && y >= 0 && x < SIZE && y < SIZE;
}

Piece::Move* Chessboard::get_last_move() {
    if (moves.empty()) return nullptr;
    return &moves[moves.size() - 1];
}

void Chessboard::set_piece(int x, int y, Piece *piece) {
    if (!is_valid_field(x, y)) return;
    clear_field(piece->get_x(), piece->get_y());
    board[x][y] = piece;
    piece->set_position(x, y);
}

std::vector<Piece*> Chessboard::get_pieces(Piece::Colour colour, Piece::Type type) {
    std::vector<Piece*> pieces;
    for (Piece* piece : this->pieces) {
        if (piece->type == type && piece->colour == colour) {
            pieces.push_back(piece);
        }
    }
    return pieces;
}

bool Chessboard::piece_exists(Piece::Colour colour, Piece::Type type) {
    for (Piece* piece : this->pieces) {
        if (piece->type == type && piece->colour == colour) {
            return true;
        }
    }
    return false;
}

bool Chessboard::piece_exists(Piece::Type type) {
    return piece_exists(Piece::LIGHT, type) || piece_exists(Piece::DARK, type);
}

void Chessboard::init_pieces(Piece::Colour colour, int pieces_y, int pawns_y) {
    for (int i = 0; i < SIZE; i++) {
        add_new_piece(PIECES_ORDER[i], colour, i, pieces_y);
        add_new_piece(Piece::PAWN, colour, i, pawns_y);
    }
    create_moves();
}

Field::ColourType Chessboard::get_field_colour(int x, int y) {
    return (x + y) % 2 == 0 ? Field::LIGHT : Field::DARK;
}

Field::ColourType Chessboard::get_field_colour(Piece *piece) {
    return get_field_colour(piece->get_x(), piece->get_y());
}

void Chessboard::create_moves() {
    create_buffer_moves();

    std::vector<Piece*> pieces = this->pieces;
    std::map<Piece*, std::vector<Piece::Move>*> moves_map;

    for (Piece* piece : pieces) {
        std::vector<Piece::Move>* buffer_moves = piece->get_moves();
        std::vector<Piece::Move>* moves = new std::vector<Piece::Move>;

        for (Piece::Move move : *buffer_moves) {
            if (is_move_valid(move)) {
                moves->push_back(move);
            }
        }
        moves_map[piece] = moves;
    }

    for (Piece* piece : pieces) {
        piece->set_moves(moves_map[piece]);
    }
}

void Chessboard::create_buffer_moves() {
    for (Piece* piece : pieces) {
        piece->create_buffer_moves();
    }
}

void Chessboard::add_new_piece(Piece::Type type, Piece::Colour colour, int x, int y) {
    Piece* piece = new Piece(type, colour, x, y, this);
    add_piece_to_list(piece);
    set_piece(x, y, piece);
}

void Chessboard::add_piece_to_list(Piece *piece) {
    pieces.push_back(piece);
}

void Chessboard::remove_piece_from_list(Piece *piece) {
    pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
}

void Chessboard::clear_field(int x, int y) {
    board[x][y] = nullptr;
}

void Chessboard::try_move_piece(Piece *piece, int x, int y) {
    for (Piece::Move move : *(piece->get_moves())) {
        if (move.x == x && move.y == y) {
            do_move(move);
            clicked_piece = nullptr;
            change_turn();
            return;
        }
    }
}

Piece* Chessboard::get_king(Piece::Colour colour) {
    for (Piece* piece : pieces) {
        if (piece->colour == colour && piece->type == Piece::KING) {
            return piece;
        }
    }
    return nullptr;
}

bool Chessboard::is_king_attacked(Piece::Colour colour) {
    return get_king(colour)->is_attacked();
}

void Chessboard::check_king_check() {
    is_check = is_king_attacked(turn);
}

bool Chessboard::is_move_valid(Piece::Move move) {
    int x = move.x;
    int y = move.y;
    int old_x = move.old_x;
    int old_y = move.old_y;
    Piece* piece = move.piece;
    Piece* captured_piece = move.captured_piece;

    set_piece(x, y, piece);
    if (captured_piece != nullptr) {
        remove_piece_from_list(captured_piece);
    }
    create_buffer_moves();

    bool is_valid = !get_king(piece->colour)->is_attacked();

    set_piece(old_x, old_y, piece);
    if (captured_piece != nullptr) {
        int captured_piece_x = captured_piece->get_x();
        int captured_piece_y = captured_piece->get_y();

        board[captured_piece_x][captured_piece_y] = captured_piece;
        add_piece_to_list(captured_piece);
    }
    create_buffer_moves();

    return is_valid;
}

bool Chessboard::is_pawn_promotion(Piece *piece, int y) {
    return piece->type == Piece::PAWN && (y == 0 || y == SIZE - 1);
}

void Chessboard::do_castling(int x, int y, int old_x) {
    int rook_x, rook_new_x;
    if (x - old_x > 0) {
        rook_x = SIZE - 1;
        rook_new_x = x - 1;
    } else {
        rook_x = 0;
        rook_new_x = x + 1;
    }

    Piece* rook = get_piece(rook_x, y);
    set_piece(rook_new_x, y, rook);
    rook->move(rook_new_x, y);
}

bool Chessboard::is_castling(Piece *piece, int new_x, int old_x) {
    return piece->type == Piece::KING && abs(new_x - old_x) == 2;
}

bool Chessboard::check_game_end() {
    if (is_king_check_mate(Piece::LIGHT)) {
        victory(Piece::LIGHT);
    } else if (is_king_check_mate(Piece::DARK)) {
        victory(Piece::DARK);
    } else if (is_draw()) {
        draw();
    } else {
        return false;
    }
    return true;
}

void Chessboard::game_end() {
    is_game_end = true;
}

void Chessboard::victory(Piece::Colour colour) {
}

void Chessboard::draw() {
}

bool Chessboard::is_king_check_mate(Piece::Colour winner) {
    Piece::Colour opponent = Piece::get_opposite_colour(winner);
    if (is_king_attacked(opponent)) {
        for (Piece* piece : pieces) {
            if (piece->colour == opponent && !piece->get_moves()->empty()) {
                return false;
            }
        }
        is_check_mate = true;
        return true;
    }
    return false;
}

bool Chessboard::is_draw() {
    bool light_stalemate = true;
    bool dark_stalemate = true;

    for (Piece* piece : pieces) {
        if (!piece->get_moves()->empty()) {
            if (piece->colour == Piece::LIGHT) {
                light_stalemate = false;
            } else {
                dark_stalemate = false;
            }
        }
    }
    if (light_stalemate || dark_stalemate) {
        return true;
    }

    if (pieces.size() == 2) {
        return true;
    }
    if (pieces.size() == 3 && (piece_exists(Piece::KNIGHT) || piece_exists(Piece::BISHOP))) {
        return true;
    }
    if (pieces.size() == 4) {
        std::vector<Piece*> light_bishops = get_pieces(Piece::LIGHT, Piece::BISHOP);
        std::vector<Piece*> dark_bishops = get_pieces(Piece::DARK, Piece::BISHOP);

        if (light_bishops.size() == 1 && dark_bishops.size() == 1) {
            if (get_field_colour(light_bishops[0]) == get_field_colour(dark_bishops[0])) {
                return true;
            }
        }
    }
    return false;
}
