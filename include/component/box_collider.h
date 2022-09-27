#pragma once

#include "component/collider.h"
#include "primitive2.h"

class Entity;

class BoxCollider : public Collider
{
private:

public:
    BoxCollider(Entity&, Box);
    ~BoxCollider() = default;

    Box     m_box;

    void    update() override;
    void    setRange(float w, float h);
};