#pragma once

#include <cstdint>
#include <vector>

#include "component.h"
#include "gold_dealer.h"
#include "timer.h"

class GoldDealer;
class Entity;

class GoldPerSecond : public Component
{
private:
    std::vector<Timer>      m_timer;
    std::vector<GoldDealer> m_dealer;
    uint16_t                m_limit = 0;

public:
    GoldPerSecond(Entity&, uint16_t gold);
    ~GoldPerSecond() = default;

    void update() override; 
};
