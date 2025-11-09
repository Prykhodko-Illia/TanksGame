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

    const float ROTATION_SPEED = 100.0f;
    void rotateToPlayer(const std::unique_ptr<ITank> &playerTank, float rotationValue);
    bool isFacingPlayer(const std::unique_ptr<ITank> &playerTank, float rotationValue);
public:
    EnemyTank(int health, int damage, floatPair position, float rotation);
    void update(const std::unique_ptr<ITank> &player, float deltaTime) override;
    bool takeDamage(int damage);
};
