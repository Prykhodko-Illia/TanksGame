#include "../../headers/entities/Projectile.h"

#include <cmath>

Projectile::Projectile(const floatPair &position, const int damage, const float rotation, const ProjectileType type)
    : m_position(position), m_damage(damage), m_rotation(rotation), m_type(type)
{ }

void Projectile::update(const float deltaTime) {
    float radians = m_rotation * M_PI / 180.0;

    float velocityX = cos(radians) * PROJECTILE_SPEED;
    float velocityY = sin(radians) * PROJECTILE_SPEED;

    float newX = m_position.first + velocityX * deltaTime;
    float newY = m_position.second + velocityY * deltaTime;

    m_position = {newX, newY};
}

bool Projectile::isAlive() const {
    return m_isAlive;
}

void Projectile::setIsAlive(const bool state) {
    m_isAlive = state;
}

int Projectile::getDamage() const {
    return m_damage;
}

ProjectileType Projectile::getType() const {
    return m_type;
}

EntityRenderInfo Projectile::getRenderInfo() const {
    const auto [first, second] = m_position;
    EntityRenderInfo info {
        first,
        second,
        m_rotation,
        PROJECTILE_SIZE,
         PROJECTILE_SIZE,
        0.2,
        "projectile",
        true
    };

    return info;
}

EntityCollisionInfo Projectile::getCollisionInfo() const {
    const auto [first, second] = m_position;
    EntityCollisionInfo info = {
        first,
        second,
        PROJECTILE_SIZE,
        PROJECTILE_SIZE
    };

    return info;
}