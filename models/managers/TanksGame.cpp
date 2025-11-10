#include "../../headers/managers/TanksGame.h"
#include <algorithm>

std::vector<TanksGame::floatPair> TanksGame::getValidPositions() {
    std::vector<floatPair> positions{};

    const auto &grid = m_map->getGrid();
    const int width = m_map->getGridWidth();
    const int height = m_map->getGridHeight();

    const std::vector<std::pair<int, int>> offsets = {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};

    for (int i = 2; i < (height - 2); ++i) {
        for (int j = 2; j < (width - 2); ++j) {
            bool isvalid = true;
            for (const auto &[x, y] : offsets) {

                if (!grid[i + y][j + x] || grid[i + y][j + x]->getType() != BlockType::Empty) {
                    isvalid = false;
                    break;
                }
            }

            if (isvalid && grid[i][j]) {
                positions.push_back(grid[i][j]->getPosition());
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
        m_player = std::move(playerTankF.createTank(PLAYER_HEALTH, PLAYER_DAMAGE, {70, 150}, 0));
    }

    const auto playerPosition = m_player->getPosition();

    m_map = generateMap(windowSize.first, windowSize.second,
        0.036, 7, playerPosition, m_blocks);
}

void TanksGame::update(const float deltaTime, const floatPair &windowSize) {
    m_projectileTimerSpawn += deltaTime;
    m_enemyTimerSpawn += deltaTime;

    for (const auto &p : m_projectiles) {
        p->update(deltaTime);
    }

    if (m_enemyTimerSpawn >= ENEMY_SPAWN_TIME) {
        this->spawnEnemy();
    }

    m_projectiles.erase(
    std::remove_if(m_projectiles.begin(), m_projectiles.end(),
        [this, windowSize](const std::unique_ptr<Projectile>& projectile) {
            if (m_collisionManager.isOutOfBounds(projectile->getCollisionInfo(), windowSize)) {
                return true;
            }

            EntityCollisionInfo projectileInfo = projectile->getCollisionInfo();

            for (auto &block : m_blocks) {
                if (m_collisionManager.collides(projectileInfo, block->getCollisionInfo())) {
                    block->takeDamage();
                    return true;
                }
            }

            if (projectile->getType() == ProjectileType::Player) {
                for (auto &tank : m_enemyTanks) {
                    if (m_collisionManager.collides(projectileInfo, tank->getCollisionInfo())) {
                        tank->takeDamage(projectile->getDamage());
                        return true;
                    }
                }
            }

            if (projectile->getType() == ProjectileType::Enemy) {
                if (m_collisionManager.collides(projectileInfo, m_player->getCollisionInfo())) {
                    m_player->takeDamage(projectile->getDamage());
                    return true;
                }
            }

            return false;
        }),
    m_projectiles.end()
    );

    m_blocks.erase(
    std::remove_if(m_blocks.begin(), m_blocks.end(),
        [](const Block* block) {
            if (!block->isAlive()) {
                delete block;
                return true;
            }
            return false;
        }),
    m_blocks.end()
    );


    auto spawnProjectile = [this](std::unique_ptr<Projectile> projectile) {
        m_projectiles.push_back(std::move(projectile));
    };

    auto canMoveTo = [this, windowSize](const EntityCollisionInfo& nextPos) {
        return m_collisionManager.canTankMoveTo(nextPos, m_blocks, m_enemyTanks, m_player, false, windowSize);
    };

    for (const auto &enemy : m_enemyTanks) {
        enemy->update(m_player, deltaTime, spawnProjectile, canMoveTo);
    }

    m_enemyTanks.erase(
    std::remove_if(m_enemyTanks.begin(), m_enemyTanks.end(),
        [this](const auto &tank) {
            if (!tank->isAlive()) {
                ++m_tanksKilled;
                return true;
            }
            return false;
        }),
    m_enemyTanks.end()
    );

    if (!m_player->isAlive()) {
        exit(0);
    }
}

void TanksGame::playerShoot() {
    if (m_projectileTimerSpawn >= PROJECTILE_SPAWN_TIME) {
        m_projectileTimerSpawn = 0.0f;
        auto newProjectile = m_player->shoot(ProjectileType::Player);
        m_projectiles.push_back(std::move(newProjectile));
    }
}

void TanksGame::playerMove(const std::string &direction, const float deltaTime, const floatPair &windowSize) {
    float moveValue = TANK_SPEED * deltaTime;
    float radians = m_player->getRotation() * M_PI / 180.f;
    float dx = std::cos(radians);
    float dy = std::sin(radians);

    floatPair moveVector{};
    if (direction == "up") {
        moveVector = {dx * moveValue, dy * moveValue};
    } else if (direction == "down") {
        moveVector = {-(dx * moveValue) * 0.7, -(dy * moveValue) * 0.7};
    }

    EntityCollisionInfo nextPosition = m_player->getCollisionInfo();
    nextPosition.posX += moveVector.first;
    nextPosition.posY += moveVector.second;

    if (m_collisionManager.canTankMoveTo(nextPosition, m_blocks, m_enemyTanks, m_player, true, windowSize)) {
        m_player->move(moveVector);
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
        m_enemyTanks.push_back(std::move(enemyTankF.createTank(ENEMY_HEALTH, ENEMY_DAMAGE, positions.at(randomPos(gen)), 0)));
    }

}

std::vector<EntityRenderInfo> TanksGame::getEntitiesRenderInfo() {
    std::vector<EntityRenderInfo> info{};

    for (const auto &block : m_blocks) {
        info.push_back(block->getRenderInfo());
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

int TanksGame::getPlayerHealth() const {
    return m_player->getHealth();
}

int TanksGame::getScore() const {
    return m_tanksKilled;
}