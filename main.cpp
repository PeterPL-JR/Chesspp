#include "graphics/Window.h"

#include "chess/Chessboard.h"
#include "chess/piece/Piece.h"

Chessboard* chessboard;
Window* window;

const float BOARD_X = (Window::WIDTH - Field::size * Chessboard::SIZE) / 2;
const float BOARD_Y = (Window::HEIGHT - Field::size * Chessboard::SIZE) / 2;

void render() {
    chessboard->draw(BOARD_X, BOARD_Y, window);
}

void mouse_clicked(int x, int y, sf::Mouse::Button button) {
    if (button == sf::Mouse::Left) {
        int board_x = x - BOARD_X;
        int board_y = y - BOARD_Y;
        chessboard->click(board_x, board_y);
    }
}

int main() {
    Piece::init();

    chessboard = new Chessboard;

    window = new Window(Window::WIDTH, Window::HEIGHT, &Window::TITLE, render);
    window->set_mouse_listener(mouse_clicked);
    window->start();
}