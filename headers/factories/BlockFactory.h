#pragma once
#include <memory>
#include "../entities/Block.h"

inline std::unique_ptr<Block> createBlock(BlockType const type, const int posX, const int posY) {
    return std::make_unique<Block>(type, posX, posY);
}