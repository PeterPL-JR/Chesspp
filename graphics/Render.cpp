#include "Render.h"
#include "Colour.h"
#include "drawable/Text.h"

Colour LIGHT_COLOUR_1(0xFFE3C387);
Colour DARK_COLOUR_1(0xFF653318);

Colour LIGHT_COLOUR_2(0xFFA0895E);
Colour DARK_COLOUR_2(0xFF351C0E);

Colour RESULT_RECT_COLOUR(0xBB363636);

const std::string LIGHT_COLOUR_NAME = "White";
const std::string DARK_COLOUR_NAME = "Black";

const int TURN_LABEL_TEXT_SIZE = 25;
const int TURN_TEXT_SIZE = TURN_LABEL_TEXT_SIZE * 3 / 2;
const int WINNER_LABEL_TEXT_SIZE = 25;
const int RESULT_TEXT_SIZE = WINNER_LABEL_TEXT_SIZE * 2;

const float TURN_X = Window::WIDTH - (Window::WIDTH - Chessboard::SIZE * Field::size) / 4;
const float TURN_Y = 5;

const float TURN_LABEL_TEXT_X = TURN_X;
const float TURN_LABEL_TEXT_Y = TURN_Y + 3;

const float TURN_TEXT_X = TURN_X;
const float TURN_TEXT_Y = TURN_Y + TURN_LABEL_TEXT_SIZE / 4 * 5 + 3;

const int RESULT_RECT_WIDTH = (Field::size - 10) * 6;
const int RESULT_RECT_HEIGHT = (Field::size - 10) * 2;
const int RESULT_RECT_X = (Window::WIDTH - RESULT_RECT_WIDTH) / 2;
const int RESULT_RECT_Y = (Window::HEIGHT - RESULT_RECT_HEIGHT) / 2;

const int RESULT_TEXT_X = Window::WIDTH / 2;
const int WINNER_LABEL_TEXT_Y = RESULT_RECT_Y + 5;
const int WINNER_TEXT_Y = RESULT_RECT_Y + 40;
const int DRAW_TEXT_Y = (Window::HEIGHT - RESULT_TEXT_SIZE) / 2;

Field LIGHT_FIELD(LIGHT_COLOUR_1, LIGHT_COLOUR_2);
Field DARK_FIELD(DARK_COLOUR_1, DARK_COLOUR_2);

Box CLICK_BOX(0xFFABA888, 0xFF737362);
Box KING_CHECK_BOX(0xFFC75F52, 0xFF8A2816);

Circle MOVE_CIRCLE(0x36000000, 0, 0.45, 0);
Circle CAPTURE_CIRCLE(0, 0x36000000, 0.85, 0.15);

Box MOVE_BOX(0xFFFFCF50, 0xFFCB9925);
Box MOVE_OLD_POS_BOX(Colour::Transparent, 0xFFCB9925);

Text TURN_TEXT("Turn:", Text::FONT, TURN_LABEL_TEXT_SIZE);
Text LIGHT_TURN_TEXT(LIGHT_COLOUR_NAME, Text::FONT, TURN_TEXT_SIZE);
Text DARK_TURN_TEXT(DARK_COLOUR_NAME, Text::FONT, TURN_TEXT_SIZE);

Rectangle GAME_RESULT_RECT(RESULT_RECT_WIDTH, RESULT_RECT_HEIGHT, RESULT_RECT_COLOUR);

Text WINNER_TEXT("Winner:", Text::FONT, WINNER_LABEL_TEXT_SIZE);
Text LIGHT_WINNER_TEXT(LIGHT_COLOUR_NAME, Text::FONT, RESULT_TEXT_SIZE);
Text DARK_WINNER_TEXT(DARK_COLOUR_NAME, Text::FONT, RESULT_TEXT_SIZE);
Text DRAW_TEXT("Draw", Text::FONT, RESULT_TEXT_SIZE);

void init_render() {
    TURN_TEXT.set_alignment(Text::CENTER);

    LIGHT_TURN_TEXT.set_colour(LIGHT_COLOUR_1);
    LIGHT_TURN_TEXT.set_alignment(Text::CENTER);
    LIGHT_TURN_TEXT.set_border(1, LIGHT_COLOUR_2);

    DARK_TURN_TEXT.set_colour(DARK_COLOUR_1);
    DARK_TURN_TEXT.set_alignment(Text::CENTER);
    DARK_TURN_TEXT.set_border(1, DARK_COLOUR_2);

    WINNER_TEXT.set_alignment(Text::CENTER);

    LIGHT_WINNER_TEXT.set_alignment(Text::CENTER);
    LIGHT_WINNER_TEXT.set_colour(LIGHT_COLOUR_1);
    LIGHT_WINNER_TEXT.set_border(2, LIGHT_COLOUR_2);

    DARK_WINNER_TEXT.set_alignment(Text::CENTER);
    DARK_WINNER_TEXT.set_colour(DARK_COLOUR_1);
    DARK_WINNER_TEXT.set_border(2, DARK_COLOUR_2);

    Colour DRAW_COLOUR_1(0xFFF0F0F0);
    Colour DRAW_COLOUR_2(0xFFAAAAAA);

    DRAW_TEXT.set_alignment(Text::CENTER);
    DRAW_TEXT.set_colour(DRAW_COLOUR_1);
    DRAW_TEXT.set_border(2, DRAW_COLOUR_2);
}

void draw_on_chessboard(Drawable* drawable, int x_offset, int y_offset, int x, int y, Window* window) {
    float xx = x_offset + x * Field::size;
    float yy = y_offset + y * Field::size;
    drawable->draw(xx, yy, window);
}

void draw_piece(Piece* piece, int x_offset, int y_offset, Window* window) {
    float x = piece->get_x() * Field::size + x_offset;
    float y = piece->get_y() * Field::size + y_offset;
    Piece::draw(piece->type, piece->colour, x, y, window);
}

void draw_move(Piece::Move move, int x, int y, Window* window) {
    Circle circle = (move.captured_piece == nullptr) ? MOVE_CIRCLE : CAPTURE_CIRCLE;
    draw_on_chessboard(&circle, x, y, move.x, move.y, window);
}

void draw_clicked_piece(Piece *clicked_piece, int x, int y, Window *window) {
    std::vector<Piece::Move>* moves = clicked_piece->get_moves();
    for (Piece::Move move : *moves) {
        draw_move(move, x, y, window);
    }
    draw_on_chessboard(&CLICK_BOX, x, y, clicked_piece->get_x(), clicked_piece->get_y(), window);
}

void draw_game_info(Chessboard* chessboard, Window* window) {
    if (chessboard->is_game()) {
        draw_turn(chessboard, window);
    } else {
        draw_game_result(chessboard, window);
    }
}

void draw_turn(Chessboard* chessboard, Window* window) {
    TURN_TEXT.draw(TURN_LABEL_TEXT_X, TURN_LABEL_TEXT_Y, window);

    if (chessboard->get_turn() == Piece::LIGHT) {
        LIGHT_TURN_TEXT.draw(TURN_TEXT_X, TURN_TEXT_Y, window);
    } else {
        DARK_TURN_TEXT.draw(TURN_TEXT_X, TURN_TEXT_Y, window);
    }
}

void draw_game_result(Chessboard* chessboard, Window* window) {
    GAME_RESULT_RECT.draw(RESULT_RECT_X, RESULT_RECT_Y, window);

    if (!chessboard->is_draw()) {
        WINNER_TEXT.draw(RESULT_TEXT_X, WINNER_LABEL_TEXT_Y, window);
    }

    if (chessboard->is_winner(Piece::LIGHT)) {
        LIGHT_WINNER_TEXT.draw(RESULT_TEXT_X, WINNER_TEXT_Y, window);
    } else if (chessboard->is_winner(Piece::DARK)) {
        DARK_WINNER_TEXT.draw(RESULT_TEXT_X, WINNER_TEXT_Y, window);
    } else {
        DRAW_TEXT.draw(RESULT_TEXT_X, DRAW_TEXT_Y, window);
    }
}