#pragma once
#include <memory>
#include <vector>
#include "../../headers/entities/Projectile.h"
#include "../../headers/entities/Block.h"
#include "../../headers/entities/tanks/ITank.h"
#include "../../structs/EntityCollisionInfo.h"

class CollisionManager {
    using floatPair = std::pair<float, float>;
private:
    bool collides(const EntityCollisionInfo &obj1, const EntityCollisionInfo &obj2);
public:
    bool canTankMoveTo(const EntityCollisionInfo& tankInfo, const std::vector<Block *> &blocks, floatPair windowSize);
    bool isOutOfBounds(const EntityCollisionInfo& entityInfo, const floatPair &windowSize);
};
