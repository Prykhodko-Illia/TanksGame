#pragma once
#include <utility>
#include "Irenderable.h"

class Projectile : public IRenderable {

    using floatPair = std::pair<float, float>;
public:
    floatPair m_position{};
    int m_damage = 0;
    float m_rotation = 0;

    static constexpr float PROJECTILE_SPEED = 260.0f;
    static constexpr float PROJECTILE_SIZE = 12.0f;

public:
    Projectile(const floatPair &position, int damage, float rotation);
    void update(float deltaTime);

    EntityRenderInfo getRenderInfo() const final;
};
