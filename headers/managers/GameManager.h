#pragma once
#include "TanksGame.h"
#include "Renderer.h"


class GameManager {
private:
    // TanksGame m_game{};
    Renderer m_renderer{};

public:
    bool init();
    void run();
};
