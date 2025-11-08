#pragma once
#include <memory>
#include "../entities/Block.h"

inline Block createBlock(BlockType const type, const float posX, const float posY, const float width, const float height) {
    return {type, posX, posY, width, height};
}