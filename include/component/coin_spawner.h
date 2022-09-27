#pragma once

#include <vector>

#include "timer.h"
#include "component.h"

class CoinSpawner : public Component
{
private:
	std::vector<Timer>	m_timer;

	void				spawn();

public:
	CoinSpawner(Entity& entity);
	~CoinSpawner() = default;

	void update() override;
};
