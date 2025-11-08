#include "../../headers/managers/GameManager.h"

bool GameManager::init() {
    if (!m_renderer.initWindow()) {
        return false;
    }

    m_game.init(m_renderer.getWindowSize());

    return true;
}

void GameManager::run() {
    while (m_renderer.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();

        sf::Event event{};
        while (m_renderer.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_renderer.close();
            }
        }

        m_game.update(deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            m_game.playerRotate(deltaTime, false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            m_game.playerRotate(deltaTime, true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            m_game.playerMove("up", deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            m_game.playerMove("down", deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            m_game.playerShoot();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            m_game.spawnEnemy(m_renderer.getWindowSize());
        }

        m_renderer.clear();
        m_renderer.draw(m_game.getEntitiesRenderInfo());
        m_renderer.display();
    }
}