#include "../../../headers/entities/tanks/EnemyTank.h"

bool EnemyTank::takeDamage(const int damage) {
    const int newHealth = this->getHealth() - damage;

    if (newHealth < 0) {
        return false;
    }

    this->setHealth(newHealth);
    return true;
}