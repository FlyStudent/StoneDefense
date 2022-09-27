#include "entity.h"

#include "utility_function.h"
#include "component/life.h"

Life::Life(Entity& en, float maxLife)
: Component(en), m_life(maxLife), m_maxLife(maxLife)
{}

void    Life::hurt(float dmg)
{
    m_life = utility::clamp<float>(m_life - dmg, 0, m_maxLife);

    if (m_life <= 0.f)
        m_entity.entityDead();
}


void    Life::heal(float heal)
{
    m_life = utility::clamp<float>(m_life + heal, 0, m_maxLife);
}

void    Life::setMaxLife(float newLife)
{
    m_maxLife = newLife;
}


