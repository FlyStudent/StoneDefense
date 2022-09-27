#pragma once

#include "component/collider.h"
#include "primitive2.h"

class Entity;

class CircleCollider : public Collider
{
private:

public:
    CircleCollider(Entity&, Circle);
    ~CircleCollider() = default;

    Circle   m_circle;

    void    update() override;
    void    setRange(float radius);
};