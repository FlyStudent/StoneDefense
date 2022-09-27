
#include "entity.h"
#include "game.h"
#include "coin_item.h"

#include "component/coin_spawner.h"

void CoinSpawner::spawn()
{
	Vector2 randomPosition = Vector2(std::rand() % (int)(SCREEN_WIDTH * 0.5f) + SCREEN_WIDTH * 0.25f, std::rand() % (int)(SCREEN_HEIGHT * 0.5f) + SCREEN_HEIGHT * 0.2f);
	m_entity.m_game.addEntity(std::make_unique<CoinItem>(m_entity.m_game, randomPosition));
	m_timer.front().startTimer();
}

CoinSpawner::CoinSpawner(Entity& entity)
	:Component(entity)
{
	m_timer.emplace_back(Timer(entity, 20.f));
	m_timer.front().startTimer();
	spawn();
}

void CoinSpawner::update()
{
	m_timer.front().update();

	if (!m_timer.front())
	{
		spawn();
	}
}
