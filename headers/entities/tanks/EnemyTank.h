#pragma once
#include "ITank.h"

enum class EnemyState {
    Predefined,
    Aggressive,
    Simple,
    COUNT
};

class EnemyTank final : public ITank {
private:
    EnemyState m_state{};
    float m_shootTime = 0;

    const float ROTATION_SPEED = 100.0f;
    const float SHOOT_TIMER = 3.5f;
    const float SHOOTING_RADIUS = 320.0f;
    const float MOVE_SPEED = 45.0f;
    void rotateToPlayer(const std::unique_ptr<ITank> &playerTank, float rotationValue);
    bool isFacingPlayer(const std::unique_ptr<ITank> &playerTank, float rotationValue);

    float getDistanceBetweenTanks(const floatPair &point1, const floatPair &point2);

    void aggressiveMovement(const std::unique_ptr<ITank> &player, const float deltaTime, ProjectileCallBack onShoot);
public:
    EnemyTank(int health, int damage, floatPair position, float rotation);
    void update(const std::unique_ptr<ITank> &player, float deltaTime, ProjectileCallBack onShoot) override;
    bool takeDamage(int damage);
};
