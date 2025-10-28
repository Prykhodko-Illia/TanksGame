#include "../../../headers/entities/tanks/ITank.h"

ITank::ITank(const int health, const int damage)
    : m_health(health), m_damage(damage) {}

void ITank::move(intPair const &moveVector) {
    m_position.first += moveVector.first;
    m_position.second += moveVector.second;
}

int ITank::getHealth() const {
    return m_health;
}

void ITank::setHealth(const int value) {
    m_health = value;
}

void ITank::setDamage(const int value) {
    m_damage += value;
}

int ITank::getDamage() const {
    return m_damage;
}

ITank::intPair ITank::getPosition() const {
    return m_position;
}
