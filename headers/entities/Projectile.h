#pragma once
#include <utility>
#include "IRenderable.h"
#include "ICollisive.h"

enum class ProjectileType {
    Player,
    Enemy
};

class Projectile : public IRenderable, public ICollisive {

    using floatPair = std::pair<float, float>;
public:
    floatPair m_position{};
    int m_damage = 0;
    float m_rotation = 0;
    bool m_isAlive = true;
    ProjectileType m_type{};

    static constexpr float PROJECTILE_SPEED = 260.0f;
    static constexpr float PROJECTILE_SIZE = 12.0f;

public:
    Projectile(const floatPair &position, int damage, float rotation, ProjectileType type);
    void update(float deltaTime);

    bool isAlive() const;
    void setIsAlive(bool state);

    int getDamage() const;

    ProjectileType getType() const;

    EntityRenderInfo getRenderInfo() const final;
    EntityCollisionInfo getCollisionInfo() const final;
};
