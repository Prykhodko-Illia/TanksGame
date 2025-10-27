#pragma once
#include "ITank.h"

class PlayerTank : public ITank{
private:
    bool m_wasSaved = false;
public:
    bool takeDamage(int damage) final;
};
