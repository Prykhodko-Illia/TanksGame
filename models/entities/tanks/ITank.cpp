#include "../../../headers/entities/tanks/ITank.h"

ITank::ITank(const int health, const int damage, floatPair position, const float rotation)
    : m_health(health), m_damage(damage), m_position(std::move(position)), m_rotation(rotation)
{}

std::unique_ptr<Projectile> ITank::shoot(ProjectileType type) const {
    floatPair pos = this->getPosition();
    float rotation = this->getRotation();

    float tankLength = 60.0f;
    float tankWidth = 50.0f;

    float centerX = pos.first;
    float centerY = pos.second;
    
    float spawnDistance = tankLength / 2.0f;

    float radians = rotation * M_PI / 180.0f;

    float spawnX = centerX + std::cos(radians) * spawnDistance;
    float spawnY = centerY + std::sin(radians) * spawnDistance;

    floatPair spawnPos = {spawnX, spawnY};

    return createProjectile(spawnPos, this->getDamage(), rotation, type);
}

void ITank::move(floatPair const &moveVector) {
    m_position.first += moveVector.first;
    m_position.second += moveVector.second;
}

void ITank::rotate(const float value) {
    m_rotation += value;
}

int ITank::getHealth() const {
    return m_health;
}

void ITank::setHealth(const int value) {
    m_health = value;
}

int ITank::getDamage() const {
    return m_damage;
}

void ITank::setDamage(const int value) {
    m_damage += value;
}

bool ITank::isAlive() const{
    return m_health > 0;
}

ITank::floatPair ITank::getPosition() const {
    return m_position;
}

float ITank::getRotation() const {
    return m_rotation;
}

EntityRenderInfo ITank::getRenderInfo() const {
    const auto [first, second] = this->getPosition();
    EntityRenderInfo info {
        first,
        second,
        m_rotation,
        TANK_WIDTH,
        TANK_HEIGHT,
        1,
        "playerTank",
        true
    };

    return info;
}

EntityCollisionInfo ITank::getCollisionInfo() const {
    const auto [first, second] = this->getPosition();
    EntityCollisionInfo info {
        first - TANK_WIDTH / 2.0f,
        second - TANK_HEIGHT / 2.0f,
        TANK_WIDTH,
        TANK_HEIGHT
    };

    return info;
}
