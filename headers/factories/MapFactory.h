#pragma once
#include <memory>
#include <random>

#include "../entities/Map.h"
#include "BlockFactory.h"

inline BlockType getGeneratedType(const std::vector<std::vector<Block>> &grid, const size_t i, const size_t j, const int density) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution prob(0, 100);
    std::uniform_int_distribution randomBlock(0, static_cast<int>(BlockType::COUNT) - 1);


    BlockType type = BlockType::Empty;
    std::vector<BlockType> neighbourType{};


    if (density <= prob(gen)) {
        return BlockType::Empty;
    }

    if (j >= 1) {
        if (i >= 1) {
            neighbourType.push_back(grid[i - 1][j - 1].getType());
        }

        neighbourType.push_back(grid[i][j - 1].getType());
    }

    if (i >= 1) {
        neighbourType.push_back(grid[i - 1][j].getType());
    }

    for (auto const newType : neighbourType) {
        if (newType != BlockType::Empty) {
            type = newType;
        }
    }

    if (type == BlockType::Empty) {
        type = static_cast<BlockType>(randomBlock(gen));
    }

    return type;
}

inline void fillGrid(const std::unique_ptr<Map> &map, const int width, const int height, const float scaleValue, const int density) {

    float posX = 0;
    float posY = 0;
    auto &grid = map->getGrid();

    const float widthIncrement = width * scaleValue;
    const float heightIncrement = height * scaleValue;

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            auto const block = createBlock(getGeneratedType(grid, i, j, density), posX, posY);
            grid[i][j] = block;

            posX += heightIncrement;
        }

        posX = 0;
        posY += widthIncrement;
    }
}

inline std::unique_ptr<Map> generateMap(const int width, const int height, const float scaleValue, const int density) {
    const float newWidth = width * scaleValue;
    const float newHeight = height * scaleValue;

    auto newMap = std::make_unique<Map>(newWidth, newHeight);

    fillGrid(newMap, newWidth, newHeight, scaleValue, density);

    return newMap;
}
