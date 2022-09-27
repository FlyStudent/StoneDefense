
#include "game.h"

#include "component/particle.h"

#include "coin_particle.h"

CoinParticle::CoinParticle(Game& game, Vector2 position)
	:Entity(game, position, false)
{
	//Particle 
	addComponent(std::make_unique<Particle>(*this, 1.f, Vector2::down, 15.f))->m_isActivate = true;;
	m_particleComp = reinterpret_cast<Particle*>(components.back().get());

	// Texture
	m_layer = 7;
	m_sprite = Sprite::COIN;
}

void CoinParticle::draw()
{
	GPTexture& texture = m_game.m_sprites[(int)m_sprite];
	float w = static_cast<float>(texture.width);
	float h = static_cast<float>(texture.height);
	gpDrawTextureEx2(m_game.m_gp, texture, {0.f, 0.f, w, h}, {m_pos.x - w/2.f, m_pos.y - h/ 2.f , w * 0.75f, h * 0.75f}, {1.f, 1.f, 1.f, 1.f - m_particleComp->getLifeTimeRatio()});
}
