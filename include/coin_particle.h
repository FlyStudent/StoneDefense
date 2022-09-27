#pragma once

#include "entity.h"

class Particle;

class CoinParticle : public Entity
{
private:
	Particle* m_particleComp = nullptr;

public:
	CoinParticle(Game& game, Vector2 position);
	~CoinParticle() = default;

	void draw() override;
};
