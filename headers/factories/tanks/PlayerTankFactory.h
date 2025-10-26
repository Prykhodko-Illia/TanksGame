#pragma once
#include "TankFactory.h"

class PlayerTankFactory : public TankFactory {
    std::unique_ptr<ITank> createTank() const final;
};

