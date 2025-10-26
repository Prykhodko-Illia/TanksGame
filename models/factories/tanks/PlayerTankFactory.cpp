#include "../../../headers/factories/tanks/PlayerTankFactory.h"
#include "../../../headers/entities/tanks/PlayerTank.h"

std::unique_ptr<ITank> PlayerTankFactory::createTank() const final {
    return std::make_unique<PlayerTank>();
}