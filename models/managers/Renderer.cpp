#include "../../headers/managers/Renderer.h"

bool Renderer::initWindow() {
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "TanksGame");

    return true;
}

bool Renderer::isOpen() const {
    return m_window.isOpen();
}

bool Renderer::pollEvent(sf::Event &event) {
    return m_window.pollEvent(event);
}

void Renderer::close() {
    m_window.close();
}

void Renderer::clear() {
    m_window.clear();
}

void Renderer::draw() {
    // m_window.draw();
}

void Renderer::display() {
    m_window.display();
}
