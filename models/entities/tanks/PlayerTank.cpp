#include "../../../headers/entities/tanks/PlayerTank.h"

PlayerTank::PlayerTank(const int health, const int damage, floatPair position, const float rotation)
    : ITank(health, damage, std::move(position), rotation) {
    m_textureId = "playerTank";
}

void PlayerTank::update(const std::unique_ptr<ITank> &player, const float deltaTime, ProjectileCallBack onShoot, MovementValidator canMoveTo) {}

void PlayerTank::takeDamage(const int damage) {
    int newHealth = this->getHealth() - damage;

    if (newHealth <= 0) {
        if (!m_wasSaved) {
            m_wasSaved = true;
            newHealth = 1;
        }
    }

    this->setHealth(newHealth);
}