#include "../../../headers/factories/tanks/PlayerTankFactory.h"

std::unique_ptr<ITank> PlayerTankFactory::createTank(const int health, const int damage, std::pair<int, int> position, const float rotation) const {
    return std::make_unique<PlayerTank>(health, damage, std::move(position), rotation);
}