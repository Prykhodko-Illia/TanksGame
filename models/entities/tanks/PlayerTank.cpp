#include "../../../headers/entities/tanks/PlayerTank.h"

void PlayerTank::takeDamage(const int damage) {
    this->setHealth(this->getHealth() - damage);
}