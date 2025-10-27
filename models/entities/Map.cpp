#include "../../headers/entities/Map.h"

Map::Map(const int width, const int height) {
    m_grid = std::vector(width, std::vector<Block>(height));
}

Map::Grid & Map::getGrid() {
    return m_grid;
}
