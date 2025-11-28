#ifndef CHESSPP_RENDER_H
#define CHESSPP_RENDER_H

#include "drawable/geometry/Box.h"
#include "drawable/geometry/Circle.h"
#include "../chess/piece/Piece.h"
#include "Window.h"

extern Field LIGHT_FIELD;
extern Field DARK_FIELD;

extern Box CLICK_BOX;

extern Circle MOVE_CIRCLE;
extern Circle CAPTURE_CIRCLE;

extern Box MOVE_BOX;
extern Box MOVE_OLD_POS_BOX;

void draw_on_chessboard(Drawable* drawable, int x_offset, int y_offset, int x, int y, Window* window);

void draw_piece(Piece& piece, int x_offset, int y_offset, Window* window);

#endif