
#include "entity.h"
#include "game.h"

#include "component/particle.h"

Particle::Particle(Entity& en, float lifeTime, Vector2 direction, float speed)
	:Component(en), m_lifeTime(lifeTime), m_direction(direction), m_speed(speed)
{}

void Particle::update()
{
	auto& gp = m_entity.m_game.m_gp;
	m_lifeTimer += m_entity.m_game.getDeltaTime();
	m_entity.m_pos += m_direction * m_speed * m_entity.m_game.getDeltaTime();

	if (m_lifeTimer > m_lifeTime)
		m_entity.m_isAlive = false;
}
