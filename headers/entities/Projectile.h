#pragma once
#include <utility>
#include "IRenderable.h"
#include "ICollisive.h"

class Projectile : public IRenderable, public ICollisive {

    using floatPair = std::pair<float, float>;
public:
    floatPair m_position{};
    int m_damage = 0;
    float m_rotation = 0;
    bool m_isAlive = true;

    static constexpr float PROJECTILE_SPEED = 260.0f;
    static constexpr float PROJECTILE_SIZE = 12.0f;

public:
    Projectile(const floatPair &position, int damage, float rotation);
    void update(float deltaTime);

    bool isAlive() const;
    void setIsAlive(bool state);

    int getDamage() const;

    EntityRenderInfo getRenderInfo() const final;
    EntityCollisionInfo getCollisionInfo() const final;
};
