#pragma once
#include "TankFactory.h"
#include "../../entities/tanks/PlayerTank.h"

class PlayerTankFactory : public TankFactory {
public:
    std::unique_ptr<ITank> createTank(int health, int damage, std::pair<int, int> position) const final;
};

