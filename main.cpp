#include "headers/managers/GameManager.h"
#include "headers/factories/MapFactory.h"

int main() {

    //
    // auto const map = generateMap(800, 1000, 0.03, 15);
    // map->printMap();

    GameManager gm;
    gm.init();
    gm.run();
    return 0;
}