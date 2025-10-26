#pragma once
#include <memory>
#include "../../entities/tanks/ITank.h"

class TankFactory {
public:
    virtual ~TankFactory() = 0;
    virtual std::unique_ptr<ITank> createTank() const = 0;
};