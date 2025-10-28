#include "../../headers/entities/Map.h"

#include <iostream>

Map::Map(const int width, const int height) {
    m_grid = std::vector(width, std::vector<Block>(height));
}

Map::Grid & Map::getGrid() {
    return m_grid;
}

void Map::printMap() const{
    for (auto row : m_grid) {
        for (auto cell : row) {
            switch (cell.getType()) {
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