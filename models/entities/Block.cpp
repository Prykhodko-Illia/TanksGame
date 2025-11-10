#include "../../headers/entities/Block.h"

Block::Block() : m_type(BlockType::Empty) {}

Block::Block(BlockType const type, const float posX, const float posY, const float width, const float height)
    : m_type(type), m_position({posX, posY}), m_width(width), m_height(height)
{
    switch (type) {
        case BlockType::Bush:
            m_durability = 1;
            break;

        case BlockType::Tree:
            m_durability = 2;
            break;

        case BlockType::Rock:
            m_durability = 3;
            break;

        default:
            m_durability = 0;
    }
}

BlockType Block::getType() const {
    return m_type;
}

std::pair<float, float> Block::getPosition() const{
    return m_position;
}

bool Block::isAlive() const {
    return m_durability > 0;
}

void Block::takeDamage() {
    --m_durability;
}

EntityRenderInfo Block::getRenderInfo() const {
    const auto [first, second] = m_position;

    std::string textureId{};
    switch (m_type) {
        case (BlockType::Bush):
            textureId = "Bush";
            break;
        case (BlockType::Tree):
            textureId = "Tree";
            break;
        case (BlockType::Rock):
            textureId = "Rock";
            break;
        default:
            return {};
    }

    EntityRenderInfo info {
        first,
        second,
        0,
        m_width,
        m_height,
        1,
        textureId,
        false
    };

    return info;
}

EntityCollisionInfo Block::getCollisionInfo() const {
    const auto [first, second] = m_position;
    EntityCollisionInfo info = {
        first,
        second,
        m_width,
        m_height
    };

    return info;
}