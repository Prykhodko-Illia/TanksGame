#pragma once
#include <utility>
#include "IRenderable.h"
#include "ICollisive.h"

enum class BlockType {
    Empty = -1,
    Bush = 0,
    Tree = 1,
    Rock = 2,
    COUNT = 3
};

class Block final : public IRenderable, public ICollisive {
private:
    BlockType m_type{};

    std::pair<float, float> m_position{};
    int m_durability = 0;
    float m_width = 0, m_height = 0;
public:
    Block();
    Block(BlockType type, float posX, float posY, float width, float height);

    BlockType getType() const;
    std::pair<float, float> getPosition() const;

    bool isAlive() const;

    void takeDamage();
    EntityRenderInfo getRenderInfo() const;
    EntityCollisionInfo getCollisionInfo() const;
};
