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

    void printMap() const; /*for debugging*/
    int getGridWidth() const;
    int getGridHeight() const;
};
