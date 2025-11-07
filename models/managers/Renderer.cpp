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

void Renderer::draw(const std::vector<EntityRenderInfo> &entities) {
    for (auto &obj : entities) {
        float width = 60.0f * obj.scaleValue;
        float height = 50.0f * obj.scaleValue;

        sf::RectangleShape sprite(sf::Vector2f(width, height));
        sprite.setOrigin(width / 2, height / 2);
        sprite.setPosition(obj.posX, obj.posY);
        sprite.setRotation(obj.rotation);
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

        if (obj.textureId == "bushBlock") {
            sprite.setFillColor(sf::Color::Green);
        } else if (obj.textureId == "woodBlock") {
            sprite.setFillColor(sf::Color{150, 75, 0});
        } else if (obj.textureId == "brickBlock") {
            sprite.setFillColor(sf::Color{100, 0, 35});
        } else if (obj.textureId == "playerTank") {
            sprite.setFillColor(sf::Color::Magenta);
        } else if (obj.textureId == "projectile") {
            sprite.setFillColor(sf::Color::Red);
        }

        m_window.draw(sprite);
    }
}

void Renderer::display() {
    m_window.display();
}
