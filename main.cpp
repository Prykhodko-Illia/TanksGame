#include "headers/managers/GameManager.h"
#include "headers/factories/MapFactory.h"

int main() {
    // GameManager gm;
    // gm.init();
    // gm.run();

    auto const map = generateMap(800, 1000, 0.03, 10);
    map->printMap();
    return 0;
}