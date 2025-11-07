#pragma once
#include <memory>
#include "../entities/Projectile.h"

inline std::unique_ptr<Projectile> createProjectile(const std::pair<float, float> &position, const int damage, const float rotation) {
    return std::make_unique<Projectile>(position, damage, rotation);
}