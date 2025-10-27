#pragma once
#include <memory>
#include "../entities/Block.h"

inline Block createBlock(BlockType const type, const int posX, const int posY) {
    return Block(type, posX, posY);
}