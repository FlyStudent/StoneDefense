
#include <gp/gp.h>

#include "game.h"
#include "entity.h"
#include "defines.h"
#include "primitive2.h"
#include "utility_function.h"

#include "component/timerbar.h"
#include "component/timer.h"

Timerbar::Timerbar(Entity& en, Timer* timer, float distance)
: Component(en), m_distance(distance)
{
    if (timer)
        m_timer = timer;
    else
        m_timer = m_entity.m_timer;
    
    m_pos = {m_entity.m_pos.x, m_entity.m_pos.y - m_distance};
    m_maxTimerState = TILE_SIZE - TILE_SIZE/10;
    m_timerState = m_maxTimerState;

    m_w = 2*TILE_SIZE/2.5;
    m_h = 2*TILE_SIZE/8.f;
    m_timerw = m_w * 0.9f;
    m_timerh = m_h * 0.7f;
}

void    Timerbar::update()
{
    m_pos = {m_entity.m_pos.x, m_entity.m_pos.y - m_distance};

    if (m_timer)
        m_timerState = (float)m_timer->getTimer() / (float)m_timer->getMaxTimer();
}

void    Timerbar::draw()
{
    auto gp = m_entity.m_game.m_gp;
    GPRect backRect = {m_pos.x - m_w/2, m_pos.y - m_h/2, m_w, m_h};
    gpDrawRectFilled(gp, backRect, GP_CBLACK);
    GPRect timerRect = {m_pos.x - m_timerw/2 , m_pos.y - m_timerh/2, m_timerState * m_timerw, m_timerh};
    gpDrawRectFilled(gp, timerRect, utility::colorHexaToFloat(0xFF155DF3));
}