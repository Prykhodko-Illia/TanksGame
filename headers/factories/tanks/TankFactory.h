#pragma once
#include <memory>
#include "../../entities/tanks/ITank.h"

class TankFactory {
public:
    virtual ~TankFactory() = default;
    virtual std::unique_ptr<ITank> createTank(int health, int damage, std::pair<int, int> position, float rotation) const = 0;
};