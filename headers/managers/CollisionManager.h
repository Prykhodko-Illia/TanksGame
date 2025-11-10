#pragma once
#include <memory>
#include <vector>
#include "../../headers/entities/Projectile.h"
#include "../../headers/entities/Block.h"
#include "../../headers/entities/tanks/ITank.h"
#include "../../structs/EntityCollisionInfo.h"

class CollisionManager {
    using floatPair = std::pair<float, float>;
public:
    bool canTankMoveTo(const EntityCollisionInfo& tankInfo, const std::vector<Block*>& blocks,
        const std::vector<std::unique_ptr<ITank>>& enemyTanks, const std::unique_ptr<ITank>& playerTank,
        bool isPlayer, floatPair windowSize, const EntityCollisionInfo* selfInfo = nullptr);
    bool isOutOfBounds(const EntityCollisionInfo& entityInfo, const floatPair &windowSize);
    bool collides(const EntityCollisionInfo &obj1, const EntityCollisionInfo &obj2);
};
