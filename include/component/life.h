#pragma once

#include <cstdint>
#include <functional>

#include "component.h"

class Entity;

class Life : public Component
{
private:
    float                m_life;
    float                m_maxLife;

public:
    Life(Entity& en, float maxLife);
    ~Life() = default;

    float    getLife() const {return m_life;}
    float    getMaxLife() const {return m_maxLife;}
    float    getRatio() const { return m_life / m_maxLife; }

    void    hurt(float);
    void    heal(float);
    void    setMaxLife(float);
};