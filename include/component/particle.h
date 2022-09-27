#pragma once

#include "primitive2.h"
#include "component.h"

class Entity;

class Particle : public Component
{
private:
    float   m_lifeTime = 1.f;
    float   m_lifeTimer = 0.f;
    Vector2 m_direction = Vector2::zero;
    float   m_speed = 5.f;
    
public:
    Particle(Entity&, float lifeTime, Vector2 direction, float speed);
    ~Particle() = default;

    void update() override;
    float getLifeTimeRatio() const { return m_lifeTimer / m_lifeTime; };
};