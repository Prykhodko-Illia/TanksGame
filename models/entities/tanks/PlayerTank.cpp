#include "../../../headers/entities/tanks/PlayerTank.h"

PlayerTank::PlayerTank(const int health, const int damage, intPair position)
    : ITank(health, damage, std::move(position))
{

}

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