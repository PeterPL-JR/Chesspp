#include "Window.h"

#include <SFML/Window.hpp>

std::string Window::TITLE = "Chess++";

Window::Window(int width, int height, std::string* title) {
    window = new sf::RenderWindow(sf::VideoMode(width, height), *title);
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

void Window::game_loop() {
    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                stop();
            }
        }

        window->clear(sf::Color::Black);
        window->display();
    }
}