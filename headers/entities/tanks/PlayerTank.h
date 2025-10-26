#pragma once
#include "ITank.h"

class PlayerTank : public ITank{

public:
    void takeDamage(int damage) final;
};
