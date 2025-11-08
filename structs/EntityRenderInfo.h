#pragma once
#include <iostream>

struct EntityRenderInfo {
    float posX = 0, posY = 0;
    float rotation = 0;
    float width, height;
    float scaleValue = 0;
    std::string textureId{};
    bool isCentered = false;
};