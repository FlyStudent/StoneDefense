
#include "entity.h"
#include "game.h"
#include "utility_function.h"
#include "component/bullet_move.h"

BulletMove::BulletMove(Entity& en, Vector2 dir, float range)
: Component(en), m_range(range) 
{
    setVelocity(dir);
}

void    BulletMove::setVelocity(Vector2 direction)
{
    m_velocity = direction;
    m_velocityLength = m_velocity.length();
}

void    BulletMove::update()
{
    auto& pos = m_entity.m_pos;
    pos += m_velocity;

    m_distance += m_velocityLength;

    if ((pos.x < -OUTSCREEN_EDGE || pos.x > SCREEN_WIDTH + OUTSCREEN_EDGE)
        || pos.y < -OUTSCREEN_EDGE || pos.y > SCREEN_HEIGHT + OUTSCREEN_EDGE
        || m_distance > m_range)
    {
        m_entity.m_isAlive = false;
    }
}


