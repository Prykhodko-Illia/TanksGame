#include "../../headers/entities/Block.h"

Block::Block(BlockType const type, const int posX, const int posY)
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
    }
}

void Block::takeDamage() {
    --m_durability;
}