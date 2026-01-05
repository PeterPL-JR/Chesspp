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

            Field field = (i + j) % 2 == 0 ? LIGHT_FIELD : DARK_FIELD;
            field.draw(xx, yy, window);
        }
    }

    if (last_move_new_pos != nullptr) {
        draw_on_chessboard(&MOVE_BOX, x, y, last_move_new_pos->x, last_move_new_pos->y, window);
    }

    if (last_move_old_pos != nullptr) {
        draw_on_chessboard(&MOVE_OLD_POS_BOX, x, y, last_move_old_pos->x, last_move_old_pos->y, window);
    }

    if (is_check) {
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
    if (!(x >= 0 && y >= 0)) return;

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
    check_king_check();
}

void Chessboard::do_move(Piece::Move move) {
    Piece* piece = move.piece;
    int x = move.x;
    int y = move.y;

    int old_x = move.old_x;
    int old_y = move.old_y;

    if (!is_valid_field(x, y)) return;

    if (is_field_taken(x, y)) {
        remove_piece(get_piece(x, y));
    }

    set_piece(x, y, piece);

    piece->move(x, y);
    moves.push_back(move);

    if (is_pawn_promotion(piece, y)) {
        Piece::Colour colour = piece->colour;
        remove_piece(piece);
        add_new_piece(Piece::QUEEN, colour, x, y);
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

bool Chessboard::is_valid_field(int x, int y) {
    return x >= 0 && y >= 0 && x < SIZE && y < SIZE;
}

void Chessboard::set_piece(int x, int y, Piece *piece) {
    if (!is_valid_field(x, y)) return;
    clear_field(piece->get_x(), piece->get_y());
    board[x][y] = piece;
    piece->set_position(x, y);
}

void Chessboard::init_pieces(Piece::Colour colour, int pieces_y, int pawns_y) {
    for (int i = 0; i < SIZE; i++) {
        add_new_piece(PIECES_ORDER[i], colour, i, pieces_y);
        add_new_piece(Piece::PAWN, colour, i, pawns_y);
    }
    create_moves();
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

void Chessboard::check_king_check() {
    Piece* king = get_king(turn);
    if (king != nullptr) {
        is_check = king->is_attacked();
    }
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
        board[x][y] = captured_piece;
        add_piece_to_list(captured_piece);
    }
    create_buffer_moves();

    return is_valid;
}

bool Chessboard::is_pawn_promotion(Piece *piece, int y) {
    return piece->type == Piece::PAWN && (y == 0 || y == SIZE - 1);
}
