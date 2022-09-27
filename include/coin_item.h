#pragma once

#include "entity.h"

class Game;
class Timer;
class GoldDealer;

class CoinItem : public Entity
{
private:

	GoldDealer*		m_goldDealer = nullptr;
	Timer*			m_spawnTimer = nullptr;

public:
	CoinItem(Game& game, Vector2 position);
	~CoinItem() = default;

	void entityClicked() override;
	void draw() override;

};
