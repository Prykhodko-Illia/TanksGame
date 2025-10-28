#pragma once
#include "TankFactory.h"

class EnemyTankFactory : public TankFactory {
    std::unique_ptr<ITank> createTank(int health, int damage) const final;
};
