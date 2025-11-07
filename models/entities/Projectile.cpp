#include "../../headers/entities/Projectile.h"

#include <cmath>

Projectile::Projectile(const floatPair &position, const int damage, const float rotation)
    : m_position(position), m_damage(damage), m_rotation(rotation)
{ }

void Projectile::update(const float deltaTime) {
    float radians = m_rotation * M_PI / 180.0;

    float velocityX = cos(radians) * m_speed;
    float velocityY = sin(radians) * m_speed;

    float newX = m_position.first + velocityX * deltaTime;
    float newY = m_position.second + velocityY * deltaTime;

    m_position = {newX, newY};
}

EntityRenderInfo Projectile::getRenderInfo() const {
    const auto [first, second] = m_position;
    EntityRenderInfo info {
        first,
        second,
        m_rotation,
        0.2,
        "projectile"
    };

    return info;
}