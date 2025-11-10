#include "../../headers/managers/Renderer.h"

bool Renderer::initWindow() {
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TanksGame");

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
        float width = obj.width;
        float height = obj.height;

        sf::RectangleShape sprite(sf::Vector2f(width, height));
        if (obj.isCentered) {
            sprite.setOrigin(width / 2, height / 2);
        }
        sprite.setPosition(obj.posX, obj.posY);
        sprite.setRotation(obj.rotation);

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

        if (true) {
            sf::RectangleShape hitbox(sf::Vector2f(width, height));

            // Use the same origin as the sprite
            if (obj.isCentered) {
                hitbox.setOrigin(width / 2, height / 2);
            }

            hitbox.setPosition(obj.posX, obj.posY);
            hitbox.setRotation(obj.rotation);
            hitbox.setFillColor(sf::Color::Transparent);
            hitbox.setOutlineColor(sf::Color::Cyan);
            hitbox.setOutlineThickness(1.0f);

            m_window.draw(hitbox);
        }
    }
}

void Renderer::display() {
    m_window.display();
}

std::pair<float, float> Renderer::getWindowSize() const {
    return {WINDOW_WIDTH, WINDOW_HEIGHT};
}