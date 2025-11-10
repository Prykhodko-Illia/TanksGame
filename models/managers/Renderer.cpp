#include "../../headers/managers/Renderer.h"

bool Renderer::loadAllAssets() {
    if (!loadAssets(m_fonts, {
    {"main", "../assets/fonts/Vipnagorgialla-Bd.otf"}
    })) {
        return false;
    }

    if (!loadAssets(m_textures, {
        {"playerTank", "../assets/images/tank1.png"},
        {"enemyTank", "../assets/images/tank3.png"},
        {"Bush", "../assets/images/Bush.png"},
        {"Tree", "../assets/images/Tree.png"},
        {"Rock", "../assets/images/Rock.png"},
        {"background", "../assets/images/background.jpg"},
        {"projectile", "../assets/images/projectile.png"},
    })) {
        return false;
    }

    return true;
}

sf::Text initText(FontManager &fontAssets, const std::string &font, const int size, const sf::Color &color, const float posX, const float posY) {
    sf::Text newText;
    newText.setFont(fontAssets.get(font));
    newText.setCharacterSize(size);
    newText.setFillColor(color);
    newText.setPosition(posX, posY);

    return newText;
}

void Renderer::initTexts() {
    m_healthText = initText(m_fonts, "main", 22, sf::Color::Black, 5.0f, 5.0f);
    m_scoreText = initText(m_fonts, "main", 22, sf::Color::Black, 5.0f, 30.0f);
}

bool Renderer::initWindow() {
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TanksGame");

    if (!loadAllAssets()) {
        std::cout << "Problem with assets loading" << std::endl;
        return false;
    }

    initTexts();

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

void Renderer::draw(const std::vector<EntityRenderInfo> &entities, const int playerHealth, const int score) {
    m_background.setTexture(m_textures.get("background"));

    sf::Vector2u textureSize = m_textures.get("background").getSize();
    sf::Vector2u windowSize = m_window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    m_background.setScale(scaleX, scaleY);

    m_window.draw(m_background);

    for (auto &obj : entities) {
        sf::Sprite sprite;
        float width = obj.width;
        float height = obj.height;

        if (m_textures.has(obj.textureId)) {
            sprite.setTexture(m_textures.get(obj.textureId));

            sf::Vector2u textureSize1 = m_textures.get(obj.textureId).getSize();
            float scaleX1 = width / textureSize1.x;
            float scaleY1 = height / textureSize1.y;
            sprite.setScale(scaleX1, scaleY1);
        }

        if (obj.isCentered) {
            sf::FloatRect bounds = sprite.getLocalBounds();
            sprite.setOrigin(bounds.width / 2, bounds.height / 2);
        }

        sprite.setPosition(obj.posX, obj.posY);
        sprite.setRotation(obj.rotation);

        m_window.draw(sprite);

        // if (true) {
        //     sf::RectangleShape hitbox(sf::Vector2f(width, height));
        //
        //     // Use the same origin as the sprite
        //     if (obj.isCentered) {
        //         hitbox.setOrigin(width / 2, height / 2);
        //     }
        //
        //     hitbox.setPosition(obj.posX, obj.posY);
        //     hitbox.setRotation(obj.rotation);
        //     hitbox.setFillColor(sf::Color::Transparent);
        //     hitbox.setOutlineColor(sf::Color::Cyan);
        //     hitbox.setOutlineThickness(1.0f);
        //
        //     m_window.draw(hitbox);
        // }
    }

    m_healthText.setString("Health: " + std::to_string(playerHealth));
    m_scoreText.setString("Score: " + std::to_string(score));
    m_window.draw(m_healthText);
    m_window.draw(m_scoreText);
}

void Renderer::display() {
    m_window.display();
}

std::pair<float, float> Renderer::getWindowSize() const {
    return {WINDOW_WIDTH, WINDOW_HEIGHT};
}