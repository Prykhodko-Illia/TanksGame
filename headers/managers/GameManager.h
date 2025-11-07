#pragma once
#include "TanksGame.h"
#include "Renderer.h"

class GameManager {
private:
    TanksGame m_game{};
    Renderer m_renderer{};
    sf::Clock m_clock{};

    std::vector<std::unique_ptr<Projectile>> projectiles{};
    static constexpr float PROJECTILE_SPAWN_TIME = 1.0f;
public:
    bool init();
    void run();
};
