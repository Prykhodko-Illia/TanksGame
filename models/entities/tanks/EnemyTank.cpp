#include "../../../headers/entities/tanks/EnemyTank.h"

#include <random>

EnemyTank::EnemyTank(const int health, const int damage)
    : ITank(health, damage)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution randomState(0, static_cast<int>(EnemyState::COUNT) - 1);

    m_state = static_cast<EnemyState>(randomState(gen));
}

bool EnemyTank::takeDamage(const int damage) {
    const int newHealth = this->getHealth() - damage;

    if (newHealth < 0) {
        return false;
    }

    this->setHealth(newHealth);
    return true;
}