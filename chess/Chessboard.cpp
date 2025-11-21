#include "Chessboard.h"
#include "Piece.h"
#include "../graphics/Colour.h"

Field Chessboard::LIGHT_FIELD(0xE3C387, 0xA0895E);
Field Chessboard::DARK_FIELD(0x653318, 0x351C0E);

Box Chessboard::CLICK_BOX(0xaba888, 0x737362);

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

    for (Piece* piece : pieces) {
        if (clicked_piece == piece) {
            int xx = x + piece->get_x() * Field::size;
            int yy = y + piece->get_y() * Field::size;
            CLICK_BOX.draw(xx, yy, window);
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
    if (clicked_piece == piece) {
        clicked_piece = nullptr;
        return;
    }

    if (piece != nullptr && piece->colour == turn) {
        clicked_piece = piece;
    }
}

Piece* Chessboard::get_piece(int x, int y) {
    if (!is_field_valid(x, y)) return nullptr;
    return board[x][y];
}

Piece::Colour Chessboard::get_turn() {
    return turn;
}

void Chessboard::change_turn() {
    turn = turn == Piece::LIGHT ? Piece::DARK : Piece::LIGHT;
}

void Chessboard::set_piece(int x, int y, Piece *piece) {
    if (!is_field_valid(x, y)) return;
    board[x][y] = piece;
}

void Chessboard::draw_piece(Piece& piece, int x_offset, int y_offset, Window* window) {
    int x = piece.get_x() * Field::size + x_offset;
    int y = piece.get_y() * Field::size + y_offset;
    Piece::draw(piece.type, piece.colour, x, y, window);
}

void Chessboard::init_pieces(Piece::Colour colour, int pieces_y, int pawns_y) {
    for (int i = 0; i < SIZE; i++) {
        add_new_piece(PIECES_ORDER[i], colour, i, pieces_y);
        add_new_piece(Piece::PAWN, colour, i, pawns_y);
    }
}

void Chessboard::add_new_piece(Piece::Type type, Piece::Colour colour, int x, int y) {
    Piece* piece = new Piece(type, colour, x, y);
    pieces.push_back(piece);
    set_piece(x, y, piece);
}

bool Chessboard::is_field_valid(int x, int y) {
    return x >= 0 && y >= 0 && x < SIZE && y < SIZE;
}