#pragma once
#include "TankFactory.h"

class EnemyTankFactory : public TankFactory {
    std::unique_ptr<ITank> createTank() const final;
};
