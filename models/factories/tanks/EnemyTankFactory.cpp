#include "../../../headers/factories/tanks/EnemyTankFactory.h"
#include "../../../headers/entities/tanks/EnemyTank.h"

std::unique_ptr<ITank> EnemyTankFactory::createTank(const int health, const int damage, std::pair<int, int> position) const {
    return std::make_unique<EnemyTank>(health, damage, std::move(position));
}