#pragma once
#include <utility>

enum class BlockType {
    Empty = -1,
    Bush = 0,
    Wood = 1,
    Brick = 2,
    COUNT = 4
};

class Block {
private:
    BlockType m_type{};

    std::pair<float, float> m_position{};
    int m_durability = 0;
public:
    Block();
    Block(BlockType type, float posX, float posY);

    BlockType getType() const;
    void takeDamage();
};
