#include "game.h"

#include "component/gold_dealer.h"
#include "component/timer.h"
#include "component/circle_collider.h"

#include "coin_particle.h"
#include "coin_item.h"

CoinItem::CoinItem(Game& game, Vector2 position)
	:Entity(game, position, false)
{
	// Texture
	m_sprite = Sprite::COIN;

	// CircleCollider
	CircleCollider* collider = reinterpret_cast<CircleCollider*>(addComponent(std::make_unique<CircleCollider>(*this, Circle(m_pos, m_game.m_sprites[(int)m_sprite].width))));
	collider->setTag((uint64_t)ColliderTag::BUTTON);
	collider->setMask((uint64_t)ColliderTag::MOUSE);
	collider->m_isActivate = true;

	m_game.m_collisionEngine->setCollider(collider);

	// GoldDealer
	m_goldDealer = reinterpret_cast<GoldDealer*>(addComponent(std::make_unique<GoldDealer>(*this, COIN_ITEM_MONEY)));

	// Timers
	m_spawnTimer = reinterpret_cast<Timer*>(addComponent(std::make_unique<Timer>(*this, 1.f)));

	m_spawnTimer->startTimer();
}

void CoinItem::entityClicked()
{
	m_goldDealer->deal();
	m_game.addEntity(std::make_unique<CoinParticle>(m_game, m_pos));
	entityDead();
}

void CoinItem::draw()
{
	GPTexture texture = m_game.m_sprites[(int)m_sprite];
	if (*m_spawnTimer)
	{
		float ratio = m_spawnTimer->getTimeRatio();
		float w = texture.width * ratio;
		float h = texture.height * ratio;
		gpDrawTextureEx2(m_game.m_gp, texture, { 0.f, 0.f, (float)texture.width, (float)texture.height }, { m_pos.x - w / 2.f, m_pos.y - h / 2.f, w, h}, GP_CWHITE);
	}
	else
	{
		gpDrawTexture(m_game.m_gp, texture, m_pos, true, GP_CWHITE);
	}
}
