#include "../../headers/managers/GameManager.h"


bool GameManager::init() {
    if (!m_renderer.initWindow()) {
        return false;
    }

    return true;
}

void GameManager::run() {
    while (m_renderer.isOpen()) {
        sf::Event event{};
        while (m_renderer.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_renderer.close();
            }
        }


        m_renderer.clear();
        m_renderer.draw();
        m_renderer.display();
    }
}