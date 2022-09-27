#pragma once

#include <cstdint>

#include "component/component.h"

class Entity;

class GoldDealer : public Component
{
private:
    uint16_t    m_goldToDeal;

public:
    GoldDealer(Entity&, uint16_t);
    ~GoldDealer() = default;

    uint16_t getGold() const {return m_goldToDeal;}

    //force the deal
    void deal();
    //deal only when the entity is dead
    void update() override;
};
