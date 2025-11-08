#pragma once
#include <utility>
#include "IRenderable.h"

enum class BlockType {
    Empty = -1,
    Bush = 0,
    Wood = 1,
    Brick = 2,
    COUNT = 4
};

class Block final : public IRenderable {
private:
    BlockType m_type{};

    std::pair<float, float> m_position{};
    int m_durability = 0;
    float m_width = 0, m_height = 0;
public:
    Block();
    Block(BlockType type, float posX, float posY, float width, float height);

    BlockType getType() const;
    void takeDamage();
    EntityRenderInfo getRenderInfo() const final;
};
