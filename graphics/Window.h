#ifndef CHESSPP_WINDOW_H
#define CHESSPP_WINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>

class Window {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = WIDTH * 3 / 4;

    static std::string TITLE;

    Window(int width, int height, std::string* title);
    ~Window();

    void start();
    void stop();

    void draw(sf::Drawable* drawable);

    void render();
private:
    sf::RenderWindow* window;

    void game_loop();
};

#endif