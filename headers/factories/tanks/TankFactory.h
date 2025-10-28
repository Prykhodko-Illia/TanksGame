#pragma once
#include <memory>
#include "../../entities/tanks/ITank.h"

class TankFactory {
public:
    virtual ~TankFactory() = default;
    virtual std::unique_ptr<ITank> createTank(int health, int damage) const = 0;
};