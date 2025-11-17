#include "graphics/Window.h"

#include "chess/Chessboard.h"
#include "chess/Piece.h"

Chessboard* chessboard;
Window* window;

const float BOARD_X = (Window::WIDTH - Field::size * Chessboard::SIZE) / 2;
const float BOARD_Y = (Window::HEIGHT - Field::size * Chessboard::SIZE) / 2;

void render() {
    chessboard->draw(BOARD_X, BOARD_Y, window);
}

int main() {
    Piece::init();

    chessboard = new Chessboard;

    window = new Window(Window::WIDTH, Window::HEIGHT, &Window::TITLE, render);
    window->start();
}