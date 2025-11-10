#pragma once
#include "../../structs/EntityCollisionInfo.h"

class ICollisive {
public:
    virtual ~ICollisive() = default;
    virtual EntityCollisionInfo getCollisionInfo() const = 0;
};