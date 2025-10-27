#include "../../headers/entities/Block.h"

Block::Block() : m_type(BlockType::Empty) {}

Block::Block(BlockType const type, const float posX, const float posY)
    : m_type(type), m_position({posX, posY})
{
    switch (type) {
        case BlockType::Bush:
            m_durability = 1;
            break;

        case BlockType::Wood:
            m_durability = 2;
            break;

        case BlockType::Brick:
            m_durability = 3;
            break;

        default:
            m_durability = 0;
    }
}

BlockType Block::getType() const {
    return m_type;
}

void Block::takeDamage() {
    --m_durability;
}