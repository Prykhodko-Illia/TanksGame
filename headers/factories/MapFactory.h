#pragma once
#include <memory>
#include <random>

#include "../entities/Map.h"
#include "BlockFactory.h"

inline BlockType getGeneratedType(const std::vector<std::vector<Block>> &grid, const size_t i, const size_t j, const int density) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution prob(0, 100);
    static std::uniform_int_distribution randomBlock(0, static_cast<int>(BlockType::COUNT) - 1);


    BlockType type = BlockType::Empty;
    std::vector<BlockType> neighbourType{};

    if (grid.empty()) {
        return BlockType::Empty;
    }

    if (i >= grid.size() || j >= grid[0].size()) {
        return BlockType::Empty;
    }

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

inline void fillGrid(const std::unique_ptr<Map> &map, const int width, const int height,
    const float widthIncrement, const float heightIncrement, const int density, const std::pair<float, float> &excludePos) {

    auto &grid = map->getGrid();

    constexpr float EXCLUDING_AREA = 70;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            const float posX = j * widthIncrement;
            const float posY = i * heightIncrement;

            const bool invalidX = (excludePos.first - EXCLUDING_AREA <= posX && posX <= excludePos.first + EXCLUDING_AREA);
            const bool invalidY = (excludePos.second - EXCLUDING_AREA <= posY && posY <= excludePos.second + EXCLUDING_AREA);

            if (!(invalidX && invalidY)) {
                auto const block = createBlock(getGeneratedType(grid, i, j, density), posX, posY, widthIncrement, heightIncrement);
                grid[i][j] = block;
            }
        }
    }
}

inline std::unique_ptr<Map> generateMap(const float width, const float height, const float scaleValue, const int density, const std::pair<float, float> &excludePos) {
    const int newWidth = static_cast<int>(width * scaleValue);
    const int newHeight = static_cast<int>(height * scaleValue);

    auto newMap = std::make_unique<Map>(newWidth, newHeight);

    const float widthIncrement = width / static_cast<float>(newWidth);
    const float heightIncrement = height / static_cast<float>(newHeight);

    fillGrid(newMap, newWidth, newHeight, widthIncrement, heightIncrement, density, excludePos);

    return newMap;
}
