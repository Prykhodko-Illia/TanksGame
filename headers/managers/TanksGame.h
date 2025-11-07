#pragma once
#include <memory>
#include <vector>

#include "../factories/tanks/PlayerTankFactory.h"
#include "../../structs/EntityRenderInfo.h"
#include "../factories/MapFactory.h"

class TanksGame {
private:
    static constexpr int PLAYER_HEALTH = 25;
    static constexpr int PLAYER_DAMAGE = 10;
    static constexpr float PROJECTILE_SPAWN_TIME = 1.0f;
    static constexpr int TANK_SPEED = 200;
    static constexpr int TANK_ROTATE_SPEED = 100;

    std::unique_ptr<ITank> m_player{};
    std::vector<std::unique_ptr<Projectile>> m_projectiles{};
    std::unique_ptr<Map> m_map{};
    float m_timerSpawn = 3.0f;
public:
    void init();
    void update(float deltaTime);

    PlayerTank* getPlayerTank();
    void playerShoot();
    void playerMove(const std::string &direction, float deltaTime);
    void playerRotate(float deltaTime, bool clockWise);
    std::vector<EntityRenderInfo> getEntitiesRenderInfo();
};

