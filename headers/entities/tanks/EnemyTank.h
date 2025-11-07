#pragma once
#include "ITank.h"

enum class EnemyState {
    Predefined,
    Aggressive,
    Simple,
    COUNT
};

class EnemyTank : public ITank {
private:
    EnemyState m_state{};
public:
    EnemyTank(int health, int damage, floatPair position, float rotation);
    bool takeDamage(int damage) final;
};
