#include "../../headers/managers/CollisionManager.h"

bool CollisionManager::collides(const EntityCollisionInfo& obj1, const EntityCollisionInfo& obj2) {
    float left1 = obj1.posX;
    float right1 = obj1.posX + obj1.width;
    float top1 = obj1.posY;
    float bottom1 = obj1.posY + obj1.height;

    float left2 = obj2.posX;
    float right2 = obj2.posX + obj2.width;
    float top2 = obj2.posY;
    float bottom2 = obj2.posY + obj2.height;

    return !(right1 <= left2 || left1 >= right2 || bottom1 <= top2 || top1 >= bottom2);
}

bool CollisionManager::canTankMoveTo(const EntityCollisionInfo& tankInfo, const std::vector<Block *> &blocks, floatPair windowSize) {
    float left = tankInfo.posX;
    float right = tankInfo.posX + tankInfo.width;
    float top = tankInfo.posY;
    float bottom = tankInfo.posY + tankInfo.height;

    if (left < 0 || right > windowSize.first || top < 0 || bottom > windowSize.second) {
        return false;
    }

    for (const auto& block : blocks) {
        if (collides(tankInfo, block->getCollisionInfo())) {
            return false;
        }
    }

    return true;
}