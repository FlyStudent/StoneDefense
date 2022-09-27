
#include <gp/gp.h>

#include "game.h"
#include "entity.h"
#include "defines.h"
#include "primitive2.h"

#include "component/lifebar.h"
#include "component/life.h"

Lifebar::Lifebar(Entity& en, Vector2 offset)
: Component(en), m_offset(offset)
{
    m_pos = m_entity.m_pos + m_offset;
    m_maxLifeState = TILE_SIZE - TILE_SIZE/10;
    m_lifeState = m_maxLifeState;

    m_w = 2*TILE_SIZE/2.5;
    m_h = 2*TILE_SIZE/8.f;
    m_lifew = m_w * 0.9f;
    m_lifeh = m_h * 0.7f;
}

void    Lifebar::update()
{
    m_pos = m_entity.m_pos + m_offset;

    if (m_entity.m_life)
        m_lifeState = (float)m_entity.m_life->getLife() / (float)m_entity.m_life->getMaxLife();
}

void    Lifebar::draw()
{
    auto gp = m_entity.m_game.m_gp;
    GPRect backRect = {m_pos.x - m_w/2, m_pos.y - m_h/2, m_w, m_h};
    gpDrawRectFilled(gp, backRect, GP_CBLACK);
    GPRect lifeRect = {m_pos.x - m_lifew/2 , m_pos.y - m_lifeh/2, m_lifeState * m_lifew, m_lifeh};
    gpDrawRectFilled(gp, lifeRect, m_lifeColor);
}