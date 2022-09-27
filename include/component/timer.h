#pragma once

#include "component/component.h"

class Entity;

class Timer : public Component
{
private:
    float m_maxTimer;
    float m_timer;

public:
    Timer(Entity&, float maxTimer);
    ~Timer() = default;

    operator bool();
    
    float   getTimer() const {return m_timer;}
    float   getMaxTimer() const {return m_maxTimer;}
    float   getTimeRatio() const { return m_timer / m_maxTimer; }

    void    startTimer();
    void    setMaxTimer(float maxTimer);
    void    update() override;
};
