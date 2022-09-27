#pragma once

#include <vector>

#include "vector2.h"
#include "component.h"
#include "timer.h"

class Entity;

class PathFinding : public Component
{
private:
    std::vector<Timer>   m_speedTimer;

    int         m_wayPointNb;
    Vector2     m_nextPoint;
    Vector2     m_dirVector;
    uint16_t    m_speed;
    uint16_t    m_originalSpeed;
    float       m_range;


public:
    PathFinding(Entity&, uint16_t speed, float range);
    ~PathFinding() = default;

    uint16_t    getSpeed() const {return m_speed;}

    void        setSpeed(float scaler);

    void    update() override;
    void    assertGoal();
};
