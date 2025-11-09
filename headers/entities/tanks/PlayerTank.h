#pragma once
#include "ITank.h"

class PlayerTank : public ITank {
private:
    bool m_wasSaved = false;
public:
    PlayerTank(int health, int damage, floatPair position, float rotation);

    void update(const std::unique_ptr<ITank> &player, float deltaTime) override;
    bool takeDamage(int damage) final;
};
