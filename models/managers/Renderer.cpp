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

void Renderer::draw(EntityRenderInfo const &object) {
    float width = 60.0f * object.scaleValue;
    float height = 50.0f * object.scaleValue;

    sf::RectangleShape sprite(sf::Vector2f(width, height));
    sprite.setFillColor(sf::Color::Red);
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(object.posX, object.posY);
    sprite.setRotation(object.rotation);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    m_window.draw(sprite);
}

void Renderer::display() {
    m_window.display();
}
