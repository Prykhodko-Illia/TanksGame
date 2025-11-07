#pragma once
#include <memory>
#include "../entities/Block.h"

inline Block createBlock(BlockType const type, const float posX, const float posY) {
    return {type, posX, posY};
}