#pragma once

#include "component/component.h"
#include "vector2.h"

class Entity;

class BulletMove : public Component
{
private:
    Vector2 m_velocity;
    float   m_velocityLength = 1.f;
    float   m_range;
    float   m_distance = 0.f;

public:
    BulletMove(Entity&, Vector2, float range);
    ~BulletMove() = default;

    void    setVelocity(Vector2);
    void    update() override;
};
