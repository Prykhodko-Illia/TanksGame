#pragma once
#include "../../structs/EntityRenderInfo.h"

class IRenderable {
public:
    virtual ~IRenderable() = default;
    virtual EntityRenderInfo getRenderInfo() = 0;
};