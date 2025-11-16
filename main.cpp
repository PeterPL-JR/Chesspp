#include "graphics/Window.h"

int main() {
    Window* window = new Window(Window::WIDTH, Window::HEIGHT, &Window::TITLE);
    window->start();
    delete window;
}