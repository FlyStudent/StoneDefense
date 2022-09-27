
#include "game.h"
#include "entity.h"

#include "component/timer.h"

Timer::Timer(Entity& en, float maxTimer)
: Component(en), m_maxTimer(maxTimer), m_timer(maxTimer) {}

Timer::operator bool()
{
    return m_isActivate;
}

void    Timer::startTimer()
{
    m_timer = 0.f;
    m_isActivate = true;
}

void    Timer::setMaxTimer(float maxTimer)
{
    if (maxTimer < 0.1f)
        maxTimer = 0.1f;

    m_maxTimer = maxTimer;
    m_timer = 0.f;
}

void    Timer::update()
{
    m_timer += m_entity.m_game.getDeltaTime();

    m_isActivate = m_timer < m_maxTimer;
}