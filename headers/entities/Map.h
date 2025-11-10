#pragma once
#include <memory>
#include <vector>
#include "Block.h"

class Map {
private:
    using Grid = std::vector<std::vector<std::unique_ptr<Block>>>;
    Grid m_grid{};

    int m_gridWidth;
    int m_gridHeight;
public:
    Map(int width, int height);

    Grid & getGrid();
    void removeBlockAt(std::pair<int, int> position);

    void printMap() const; /*temporary*/
    int getGridWidth() const;
    int getGridHeight() const;
};
