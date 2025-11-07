#pragma once
#include <memory>
#include "../factories/tanks/PlayerTankFactory.h"
#include "../../structs/EntityRenderInfo.h"

class TanksGame {
private:
    static constexpr int PLAYER_HEALTH = 25;
    static constexpr int PLAYER_DAMAGE = 10;

    std::unique_ptr<ITank> m_player{};
public:
    // TanksGame();
    void init();

    PlayerTank* getPlayerTank();
};

