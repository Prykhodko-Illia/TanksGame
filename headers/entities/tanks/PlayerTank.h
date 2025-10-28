#pragma once
#include "ITank.h"

class PlayerTank : public ITank{
private:
    bool m_wasSaved = false;
public:
    PlayerTank(int health, int damage);
    bool takeDamage(int damage) final;
};
