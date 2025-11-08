#pragma once
#include "TankFactory.h"

class EnemyTankFactory : public TankFactory {
public:
    std::unique_ptr<ITank> createTank(int health, int damage, std::pair<int, int> position, float rotation) const final;
};
