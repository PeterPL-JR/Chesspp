#include "graphics/Window.h"

void render() {
}

int main() {
    Window* window = new Window(Window::WIDTH, Window::HEIGHT, &Window::TITLE, render);
    window->start();
    delete window;
}