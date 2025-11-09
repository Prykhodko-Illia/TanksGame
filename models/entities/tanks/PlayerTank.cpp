#include "../../../headers/entities/tanks/PlayerTank.h"

PlayerTank::PlayerTank(const int health, const int damage, floatPair position, const float rotation)
    : ITank(health, damage, std::move(position), rotation)
{}

void PlayerTank::update(const std::unique_ptr<ITank> &player, const float deltaTime) {}

bool PlayerTank::takeDamage(const int damage) {
    int newHealth = this->getHealth() - damage;

    if (newHealth <= 0) {
        if (m_wasSaved) {
            return false;
        }

        m_wasSaved = true;
        newHealth = 1;
    }

    this->setHealth(newHealth);
    return true;
}