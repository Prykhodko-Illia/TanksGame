#include "../../headers/managers/TanksGame.h"
#include <algorithm>

std::vector<TanksGame::floatPair> TanksGame::getValidPositions() {
    std::vector<floatPair> positions{};

    const auto grid = m_map->getGrid();
    const int width = m_map->getGridWidth();
    const int height = m_map->getGridHeight();

    const std::vector<std::pair<int, int>> offsets = {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};

    for (int i = 2; i < (height - 2); ++i) {
        for (int j = 2; j < (width - 2); ++j) {
            bool isvalid = true;
            for (const auto &[x, y] : offsets) {

                if (grid[i + y][j + x].getType() != BlockType::Empty) {
                    isvalid = false;
                    break;
                }
            }

            if (isvalid) {
                positions.push_back(grid[i][j].getPosition());
            }
        }
    }

    return positions;
}

void TanksGame:: validateEnemySpawnByTank(const std::unique_ptr<ITank> &tank, std::vector<floatPair> &positions, const float radius) {
    const auto &[playerX, playerY] = tank->getPosition();

    positions.erase(std::remove_if(positions.begin(), positions.end(),
        [playerX, playerY, radius](const auto &enemyPos) {
            return std::sqrt(std::pow((playerX - enemyPos.first), 2) + std::pow((playerY - enemyPos.second), 2)) < radius;
    }), positions.end());
}

void TanksGame::validateEnemySpawnByTanks(std::vector<floatPair> &positions) {
    validateEnemySpawnByTank(m_player, positions, 70.0f);

    for (const auto &enemy : m_enemyTanks) {
        validateEnemySpawnByTank(enemy, positions, 100.0f);
    }
}

void TanksGame::init(const floatPair &windowSize) {
    {
        auto const playerTankF = PlayerTankFactory();
        m_player = std::move(playerTankF.createTank(PLAYER_HEALTH, PLAYER_DAMAGE, {70, 50}, 0));
    }

    const auto playerPosition = m_player->getPosition();

    m_map = generateMap(windowSize.first, windowSize.second, 0.036, 12, playerPosition);
    m_map->printMap();
}

void TanksGame::update(const float deltaTime) {
    m_projectileTimerSpawn += deltaTime;
    m_enemyTimerSpawn += deltaTime;

    for (const auto &p : m_projectiles) {
        p->update(deltaTime);
    }

    auto spawnProjectile = [this](std::unique_ptr<Projectile> projectile) {
        m_projectiles.push_back(std::move(projectile));
    };

    for (const auto &enemy : m_enemyTanks) {
        enemy->update(m_player, deltaTime, spawnProjectile);
    }
}

PlayerTank* TanksGame::getPlayerTank() {
    return dynamic_cast<PlayerTank*>(m_player.get());
}

void TanksGame::playerShoot() {
    if (m_projectileTimerSpawn >= PROJECTILE_SPAWN_TIME) {
        m_projectileTimerSpawn = 0.0f;
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

void TanksGame::spawnEnemy() {
    std::random_device rd;
    std::mt19937 gen(rd());

    auto positions = getValidPositions();
    validateEnemySpawnByTanks(positions);
    std::uniform_int_distribution<int> randomPos(0, positions.size() - 1);

    if (positions.empty()) {
        std::cout << "No available positions for the tank" << std::endl;
        return;
    }

    if (m_enemyTimerSpawn >= ENEMY_SPAWN_TIME) {
        m_enemyTimerSpawn = 0.0f;
        auto const enemyTankF = EnemyTankFactory();
        m_enemyTanks.push_back(std::move(enemyTankF.createTank(PLAYER_HEALTH, PLAYER_DAMAGE, positions.at(randomPos(gen)), -180)));
    }

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

    for (const auto &e : m_enemyTanks) {
        info.push_back(e->getRenderInfo());
    }

    info.push_back(m_player->getRenderInfo());

    return info;
}