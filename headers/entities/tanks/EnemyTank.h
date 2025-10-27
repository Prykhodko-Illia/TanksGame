#pragma once
#include "ITank.h"

enum class EnemyState {
    Predefined,
    Aggressive,
    Simple
};

class EnemyTank : public ITank {
private:
    EnemyState m_state{};
public:
    bool takeDamage(int damage) final;
};
