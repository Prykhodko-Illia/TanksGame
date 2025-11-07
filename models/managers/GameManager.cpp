#include "../../headers/managers/GameManager.h"

#include <cmath>


bool GameManager::init() {
    if (!m_renderer.initWindow()) {
        return false;
    }

    m_game.init();

    return true;
}

void GameManager::run() {
    float TIMER_PROJECTILE_SPAWN = 3.0f;

    while (m_renderer.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();

        sf::Event event{};
        while (m_renderer.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_renderer.close();
            }
        }

        auto player = m_game.getPlayerTank();
        int tankSpeed = 200;

        float moveValue = tankSpeed * deltaTime;
        float radians = player->getRotation() * 3.14159f / 180.f;
        float dx = std::cos(radians);
        float dy = std::sin(radians);

        TIMER_PROJECTILE_SPAWN += deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player->rotate(-deltaTime * 100);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player->rotate(deltaTime * 100);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            player->move({dx * moveValue, dy * moveValue});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player->move({-(dx * moveValue), -(dy * moveValue)});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && TIMER_PROJECTILE_SPAWN >= PROJECTILE_SPAWN_TIME) {
            TIMER_PROJECTILE_SPAWN = 0.0f;
            auto newProjectile = player->shoot();
            projectiles.push_back(std::move(newProjectile));
        }

        m_renderer.clear();
        m_renderer.draw(player->getRenderInfo());
        for (const auto &p : projectiles) {
            p->update(deltaTime);
            m_renderer.draw(p->getRenderInfo());
        }

        m_renderer.display();
    }
}