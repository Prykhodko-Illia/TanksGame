#pragma once
#include <utility>
#include <cmath>
#include "../../../structs/EntityRenderInfo.h"
#include "../../../headers/factories/ProjectileFactory.h"
#include "../../entities/Irenderable.h"


class ITank : public IRenderable {
public:
    using floatPair = std::pair<float, float>;

    ITank(int health, int damage, floatPair position, float rotation);
    virtual ~ITank() = default;
    virtual void update(const std::unique_ptr<ITank> &player, float deltaTime) = 0;
    virtual bool takeDamage(int amount) = 0;

    std::unique_ptr<Projectile> shoot() const;
    void move(floatPair const &moveVector);
    void rotate(float value);

    int getHealth() const;
    void setHealth(int value);

    int getDamage() const;
    void setDamage(int value);

    floatPair getPosition() const;
    float getRotation() const;
    EntityRenderInfo getRenderInfo() const final;

private:
    int m_health = 0;
    int m_damage = 0;

    float m_rotation = 0;
    floatPair m_position{};
    static constexpr float TANK_WIDTH = 50.0f;
    static constexpr float TANK_HEIGHT = 42.0f;
};
