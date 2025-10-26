#include "../../../headers/factories/tanks/EnemyTankFactory.h"
#include "../../../headers/entities/tanks/EnemyTank.h"

std::unique_ptr<ITank> EnemyTankFactory::createTank() const final {
    return std::make_unique<EnemyTank>();
}