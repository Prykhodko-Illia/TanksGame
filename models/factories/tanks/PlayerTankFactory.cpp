#include "../../../headers/factories/tanks/PlayerTankFactory.h"

std::unique_ptr<ITank> PlayerTankFactory::createTank(const int health, const int damage, std::pair<int, int> position) const {
    return std::make_unique<PlayerTank>(health, damage, std::move(position));
}