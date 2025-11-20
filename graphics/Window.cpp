#include "Window.h"

std::string Window::TITLE = "Chess++";

Window::Window(int width, int height, std::string* title, void (&render_func)()) : render_func(render_func) {
    window = new sf::RenderWindow(sf::VideoMode(width, height), *title, sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);
}

Window::~Window() {
    delete window;
}

void Window::start() {
    game_loop();
}

void Window::stop() {
    window->close();
}

void Window::draw(sf::Drawable* drawable) {
    window->draw(*drawable);
}

void Window::render() {
    render_func();
}

void Window::set_mouse_listener(void (*mouse_listener)(int, int, sf::Mouse::Button)) {
    this->mouse_listener = mouse_listener;
}

void Window::game_loop() {
    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop();
            }
            if (event.type == sf::Event::MouseButtonPressed && mouse_listener != nullptr) {
                (*mouse_listener)(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
            }
        }

        window->clear(sf::Color::Black);
        render();
        window->display();
    }
}