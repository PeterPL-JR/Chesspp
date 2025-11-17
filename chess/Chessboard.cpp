#include "Chessboard.h"

Field Chessboard::LIGHT_FIELD(sf::Color(227, 195, 135), sf::Color(160, 137, 94));
Field Chessboard::DARK_FIELD(sf::Color(101, 51, 24), sf::Color(53, 28, 14));

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

    for (Piece& piece : pieces) {
        draw_piece(piece, x, y, window);
    }
}


void Chessboard::draw_piece(Piece& piece, int x_offset, int y_offset, Window* window) {
    int x = piece.get_x() * Field::size + x_offset;
    int y = piece.get_y() * Field::size + y_offset;
    Piece::draw(piece.type, piece.colour, x, y, window);
}

void Chessboard::init_pieces(Piece::Colour colour, int pieces_y, int pawns_y) {
    for (int i = 0; i < SIZE; i++) {
        pieces.push_back(Piece(PIECES_ORDER[i], colour, i, pieces_y));
        pieces.push_back(Piece(Piece::PAWN, colour, i, pawns_y));
    }
}
