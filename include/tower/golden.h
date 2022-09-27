#pragma once

#include "tower.h"

class GoldPerSecond;

class GoldenTower : public Tower
{
private:
    GoldPerSecond* m_dealer;

public:
    GoldenTower(Game& game);
    ~GoldenTower() = default;

    void    entityDropped() override;

    void    draw() override;
};
