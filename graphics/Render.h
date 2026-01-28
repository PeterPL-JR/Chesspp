#ifndef CHESSPP_RENDER_H
#define CHESSPP_RENDER_H

#include "drawable/geometry/Box.h"
#include "drawable/geometry/Circle.h"
#include "../chess/piece/Piece.h"
#include "Window.h"
#include "../chess/Chessboard.h"
#include "drawable/Text.h"
#include "drawable/geometry/Rectangle.h"

extern Field LIGHT_FIELD;
extern Field DARK_FIELD;

extern Box CLICK_BOX;
extern Box KING_CHECK_BOX;

extern Circle MOVE_CIRCLE;
extern Circle CAPTURE_CIRCLE;

extern Box MOVE_BOX;
extern Box MOVE_OLD_POS_BOX;

extern Text TURN_TEXT;
extern Text LIGHT_TURN_TEXT;
extern Text DARK_TURN_TEXT;

extern Rectangle GAME_RESULT_RECT;

extern Text WINNER_TEXT;
extern Text LIGHT_WINNER_TEXT;
extern Text DARK_WINNER_TEXT;
extern Text DRAW_TEXT;

void init_render();

void draw_on_chessboard(Drawable* drawable, int x_offset, int y_offset, int x, int y, Window* window);

void draw_piece(Piece* piece, int x_offset, int y_offset, Window* window);

void draw_move(Piece::Move move, int x, int y, Window* window);

void draw_clicked_piece(Piece* clicked_piece, int x, int y, Window* window);

void draw_game_info(Chessboard* chessboard, Window* window);

void draw_turn(Chessboard* chessboard, Window* window);
void draw_game_result(Chessboard* chessboard, Window* window);

#endif