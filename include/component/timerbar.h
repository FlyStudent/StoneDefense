#pragma once

#include "vector2.h"
#include "component/component.h"

struct GPLib;
class Entity;
class Timer;

class Timerbar : public Component
{
private:
    Timer*  m_timer = nullptr;
    Vector2 m_pos;
    float   m_maxTimerState;
    float   m_timerState;
    float   m_distance;

    float   m_w;
    float   m_h;
    float   m_timerw;
    float   m_timerh;

public:
    Timerbar(Entity&, Timer* timer, float distance);
    ~Timerbar() = default;

    void    update() override;
    void    draw();
};