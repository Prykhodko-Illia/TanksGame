#pragma once
#include <memory>
#include "../entities/Block.h"

inline std::unique_ptr<Block> createBlock(BlockType const type, const float posX, const float posY, const float width, const float height) {
    return std::make_unique<Block>(type, posX, posY, width, height);
}