#pragma once
#include "ITank.h"

enum class EnemyState {
    Aggressive,
    Defensive,
    COUNT
};

class EnemyTank final : public ITank {
private:
    EnemyState m_state{};
    float m_shootTime = 0;

    const float ROTATION_SPEED = 100.0f;
    const float SHOOT_TIMER = 3.5f;
    const float SHOOTING_RADIUS = 260.0f;

    const float MOVE_SPEED = 35.0f;

    void rotateToPlayer(const std::unique_ptr<ITank> &playerTank, float rotationValue);
    bool isFacingPlayer(const std::unique_ptr<ITank> &playerTank, float rotationValue);

    float getDistanceBetweenTanks(const floatPair &point1, const floatPair &point2);
    // void setMovePoints(const std::vector<floatPair> &movePoints);

    void aggressiveMovement(const std::unique_ptr<ITank> &player, float deltaTime,
        ProjectileCallBack onShoot, MovementValidator canMoveTo);
    void defensiveMovement(const std::unique_ptr<ITank> &player, float deltaTime, ProjectileCallBack onShoot);
    // void predefinedMovement(float deltaTime);
public:
    EnemyTank(int health, int damage, floatPair position, float rotation);
    void update(const std::unique_ptr<ITank> &player, float deltaTime,
        ProjectileCallBack onShoot, MovementValidator canMoveTo) override;
    bool takeDamage(int damage);
};
