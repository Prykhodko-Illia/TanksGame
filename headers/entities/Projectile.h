#pragma once
#include <utility>
#include "Irenderable.h"

class Projectile : public IRenderable {

    using floatPair = std::pair<float, float>;
public:
    floatPair m_position{};
    int m_damage = 0;
    float m_rotation = 0;

    static constexpr float m_speed = 260.0f;

public:
    Projectile(const floatPair &position, int damage, float rotation);
    void update(float deltaTime);

    EntityRenderInfo getRenderInfo() final;
};
