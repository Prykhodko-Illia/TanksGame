#include "../../headers/entities/Map.h"
#include <iostream>

Map::Map(const int width, const int height) : m_gridWidth(width), m_gridHeight(height)
{
    m_grid.resize(height);
    for (auto& row : m_grid) {
        row.resize(width);
    }
}

Map::Grid & Map::getGrid() {
    return m_grid;
}

void Map::printMap() const{
    for (const auto &row : m_grid) {
        for (const auto &cell : row) {
            switch (cell->getType()) {
                case BlockType::Bush:
                    std::cout << "*";
                    break;

                case BlockType::Wood:
                    std::cout << "@";
                    break;

                case BlockType::Brick:
                    std::cout << "=";
                    break;

                default:
                    std::cout << " ";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

int Map::getGridWidth() const {
    return m_gridWidth;
}

int Map::getGridHeight() const {
    return m_gridHeight;
}