#include "../../headers/managers/TanksGame.h"

void TanksGame::init(const std::pair<float, float> &windowSize) {
    {
        auto const playerTankF = PlayerTankFactory();
        m_player = std::move(playerTankF.createTank(PLAYER_HEALTH, PLAYER_DAMAGE, {50, 50}, 0));
    }

    m_map = generateMap(windowSize.first, windowSize.second, 0.025, 10);
    m_map->printMap();
}

void TanksGame::update(const float deltaTime) {
    m_timerSpawn += deltaTime;

    for (const auto &p : m_projectiles) {
        p->update(deltaTime);
    }
}

PlayerTank* TanksGame::getPlayerTank() {
    return dynamic_cast<PlayerTank*>(m_player.get());
}

void TanksGame::playerShoot() {
    if (m_timerSpawn >= PROJECTILE_SPAWN_TIME) {
        m_timerSpawn = 0.0f;
        auto newProjectile = m_player->shoot();
        m_projectiles.push_back(std::move(newProjectile));
    }
}

void TanksGame::playerMove(const std::string &direction, const float deltaTime) {
    float moveValue = TANK_SPEED * deltaTime;
    float radians = m_player->getRotation() * 3.14159f / 180.f;
    float dx = std::cos(radians);
    float dy = std::sin(radians);

    if (direction == "up") {
        m_player->move({dx * moveValue, dy * moveValue});
    } else if (direction == "down") {
        m_player->move({-(dx * moveValue) * 0.7, -(dy * moveValue) * 0.7});
    }
}

void TanksGame::playerRotate(const float deltaTime, const bool clockWise) {
    clockWise ? m_player->rotate(deltaTime * TANK_ROTATE_SPEED) : m_player->rotate(-deltaTime * TANK_ROTATE_SPEED);
}

std::vector<EntityRenderInfo> TanksGame::getEntitiesRenderInfo() {
    std::vector<EntityRenderInfo> info{};

    const auto & grid = m_map->getGrid();

    for (auto &row : grid) {
        for (auto &cell : row) {
            const auto &renderInfo = cell.getRenderInfo();
            if (!renderInfo.textureId.empty()) {
                info.push_back(renderInfo);
            }
        }
    }

    for (const auto &p : m_projectiles) {
        info.push_back(p->getRenderInfo());
    }

    info.push_back(m_player->getRenderInfo());

    return info;
}