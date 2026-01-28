#ifndef CHESSPP_WINDOW_H
#define CHESSPP_WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
    static constexpr int WIDTH = 850;
    static constexpr int HEIGHT = WIDTH * 2 / 3;

    static std::string TITLE;

    Window(int width, int height, std::string* title, void (&render_func)());
    ~Window();

    void start();
    void stop();

    void draw(sf::Drawable* drawable);

    void render();

    void set_mouse_listener(void (*mouse_listener)(int, int, sf::Mouse::Button));
private:
    sf::RenderWindow* window;
    void (&render_func)();
    void (*mouse_listener)(int, int, sf::Mouse::Button) = nullptr;

    void game_loop();
};

#endif