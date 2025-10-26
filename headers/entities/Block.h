#pragma once
#include <utility>

enum class BlockType {
    Bush,
    Wood,
    Brick
};


class Block {
private:
    BlockType m_type{};

    std::pair<int, int> m_position{};
    int m_durability = 0;
public:
    Block(BlockType type, int posX, int posY);
    void takeDamage();
};
