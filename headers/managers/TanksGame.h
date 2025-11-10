#pragma once
#include <memory>
#include <vector>
#include "../factories/tanks/PlayerTankFactory.h"
#include "../factories/tanks/EnemyTankFactory.h"
#include "../../structs/EntityRenderInfo.h"
#include "../factories/MapFactory.h"
#include "CollisionManager.h"

class TanksGame {
    using floatPair = std::pair<float, float>;
private:
    static constexpr int PLAYER_HEALTH = 25;
    static constexpr int PLAYER_DAMAGE = 10;
    static constexpr float PROJECTILE_SPAWN_TIME = 1.0f;
    static constexpr float ENEMY_SPAWN_TIME = 0.3f;
    static constexpr int TANK_SPEED = 200;
    static constexpr int TANK_ROTATE_SPEED = 140;

    CollisionManager m_collisionManager{};

    std::unique_ptr<ITank> m_player{};
    std::vector<std::unique_ptr<Projectile>> m_projectiles{};
    std::vector<std::unique_ptr<ITank>> m_enemyTanks{};
    std::unique_ptr<Map> m_map{};
    std::vector<Block *> m_blocks{};
    float m_projectileTimerSpawn = 3.0f;
    float m_enemyTimerSpawn = 6.0f;

    std::vector<floatPair> getValidPositions();
    void validateEnemySpawnByTank(const std::unique_ptr<ITank> &tank, std::vector<floatPair> &positions, float radius);
    void validateEnemySpawnByTanks(std::vector<floatPair> &positions);
public:
    void init(const floatPair &windowSize);
    void update(float deltaTime, const floatPair &windowSize);

    void playerShoot();
    void playerMove(const std::string &direction, float deltaTime, const floatPair &windowSize);
    void playerRotate(float deltaTime, bool clockWise);

    void spawnEnemy();
    std::vector<EntityRenderInfo> getEntitiesRenderInfo();
};

