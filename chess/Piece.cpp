#include "Piece.h"
#include "Field.h"

#include "Move.h"

std::map<Piece::Type, std::map<Piece::Colour, std::unique_ptr<Image>>> Piece::IMAGES;
std::map<Piece::Type, std::vector<Piece::Move>* (*)(Piece*)> Piece::GET_MOVES_FUNCTIONS = {
    {PAWN, &pawn_move},
    {ROOK, &rook_move},
    {KNIGHT, &knight_move},
    {BISHOP, &bishop_move},
    {QUEEN, &queen_move},
    {KING, &king_move}
};

sf::Texture TEXTURE = Image::load_texture("chess");

constexpr int IMG_PIECE_SIZE = 16;

Piece::Piece(Type type, Colour colour, int x, int y) : type(type), colour(colour), x(x), y(y), get_moves_func(GET_MOVES_FUNCTIONS[type]) {
    image = IMAGES[type][colour].get();
}

void Piece::init() {
    init_piece_type(PAWN, 0);
    init_piece_type(ROOK, 1);
    init_piece_type(KNIGHT, 2);
    init_piece_type(BISHOP, 3);
    init_piece_type(QUEEN, 4);
    init_piece_type(KING, 5);
}

void Piece::draw(Type type, Colour colour, float x, float y, Window *window) {
    IMAGES[type][colour].get()->draw(x, y, window);
}

int Piece::get_x() {
    return x;
}

int Piece::get_y() {
    return y;
}

void Piece::update_moves() {
    moves = get_moves_func(this);
}

std::vector<Piece::Move>* Piece::get_moves() {
    return moves;
}

void Piece::init_piece_type(Type type, int tex_pos) {
    int x_pos = tex_pos * IMG_PIECE_SIZE;
    IMAGES[type][LIGHT] = std::make_unique<Image>(&TEXTURE, x_pos, 0, IMG_PIECE_SIZE, IMG_PIECE_SIZE, Field::size, Field::size);
    IMAGES[type][DARK] = std::make_unique<Image>(&TEXTURE, x_pos, IMG_PIECE_SIZE, IMG_PIECE_SIZE, IMG_PIECE_SIZE, Field::size, Field::size);
}
