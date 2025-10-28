#pragma once
#include <vector>
#include "Block.h"

class Map {
private:
    using Grid = std::vector<std::vector<Block>>;
    Grid m_grid{};

public:
    Map(int width, int height);

    Grid & getGrid();
    void removeBlockAt(std::pair<int, int> position);

    void printMap() const; /*temporary*/
};
