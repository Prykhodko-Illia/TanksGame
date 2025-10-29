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
    EnemyTank(int health, int damage, intPair position);
    bool takeDamage(int damage) final;
};
