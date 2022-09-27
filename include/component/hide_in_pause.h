#pragma once

#include "component.h"

class HideInPause : public Component
{
private:

public:
	HideInPause(Entity& entity) :Component(entity){};
	~HideInPause() = default;

	void update() override;
};
