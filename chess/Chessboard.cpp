#include "Chessboard.h"

Field Chessboard::LIGHT_FIELD(sf::Color(227, 195, 135), sf::Color(160, 137, 94));
Field Chessboard::DARK_FIELD(sf::Color(101, 51, 24), sf::Color(53, 28, 14));

void Chessboard::draw(int x, int y, Window* window) {
    for (int i = 0; i < SIZE; i++) {
        float xx = x + i * Field::size;
        for (int j = 0; j < SIZE; j++) {
            float yy = y + j * Field::size;

            Field field = (i + j) % 2 == 0 ? LIGHT_FIELD : DARK_FIELD;
            field.draw(xx, yy, window);
        }
    }
}
