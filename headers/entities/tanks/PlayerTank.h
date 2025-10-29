#pragma once
#include "ITank.h"

class PlayerTank : public ITank {
private:
    bool m_wasSaved = false;
public:
    PlayerTank(int health, int damage, intPair position);
    bool takeDamage(int damage) final;
};
