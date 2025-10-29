#include "../../headers/managers/TanksGame.h"

void TanksGame::init() {
    auto const playerTankF = PlayerTankFactory();
    m_player = std::move(playerTankF.createTank(PLAYER_HEALTH, PLAYER_DAMAGE, {50, 50}));
}
