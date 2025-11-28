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

    if (clicked_piece != nullptr) {
        std::vector<Piece::Move>* moves = clicked_piece->get_moves();
        for (Piece::Move move : *moves) {
            Piece* piece = get_piece(move.x, move.y);
            Circle circle = (piece == nullptr) ? MOVE_CIRCLE : CAPTURE_CIRCLE;
            draw_on_chessboard(&circle, x, y, move.x, move.y, window);
        }
    }

    for (Piece* piece : pieces) {
        if (clicked_piece == piece) {
            draw_on_chessboard(&CLICK_BOX, x, y, piece->get_x(), piece->get_y(), window);
        }
        draw_piece(*piece, x, y, window);
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

Piece::Colour Chessboard::get_turn() {
    return turn;
}

void Chessboard::change_turn() {
    turn = turn == Piece::LIGHT ? Piece::DARK : Piece::LIGHT;
    update_pieces();
}

void Chessboard::move_piece(Piece *piece, int x, int y) {
    int old_x = piece->get_x();
    int old_y = piece->get_y();

    if (!is_valid_field(x, y)) return;

    if (is_field_taken(x, y)) {
        remove_piece(get_piece(x, y));
    }

    board[old_x][old_y] = nullptr;
    board[x][y] = piece;

    piece->move(x, y);

    last_move_new_pos = new Field::Pos{x, y};
    last_move_old_pos = new Field::Pos{old_x, old_y};
}

void Chessboard::remove_piece(Piece *piece) {
    board[piece->get_x()][piece->get_y()] = nullptr;
    pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
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
    board[x][y] = piece;
}

void Chessboard::init_pieces(Piece::Colour colour, int pieces_y, int pawns_y) {
    for (int i = 0; i < SIZE; i++) {
        add_new_piece(PIECES_ORDER[i], colour, i, pieces_y);
        add_new_piece(Piece::PAWN, colour, i, pawns_y);
    }
    update_pieces();
}

void Chessboard::update_pieces() {
    for (Piece* piece : pieces) {
        if (piece->colour == turn) {
            piece->update_moves();
        }
    }
}

void Chessboard::add_new_piece(Piece::Type type, Piece::Colour colour, int x, int y) {
    Piece* piece = new Piece(type, colour, x, y, this);
    pieces.push_back(piece);
    set_piece(x, y, piece);
}

void Chessboard::try_move_piece(Piece *piece, int x, int y) {
    for (Piece::Move move : *(piece->get_moves())) {
        if (move.x == x && move.y == y) {
            move_piece(piece, x, y);
            clicked_piece = nullptr;
            change_turn();
            return;
        }
    }
}