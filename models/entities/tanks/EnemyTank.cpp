#include "../../../headers/entities/tanks/EnemyTank.h"

void EnemyTank::takeDamage(const int damage) {
    this->setHealth(this->getHealth() - damage);
}