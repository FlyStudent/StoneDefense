#pragma once

#include "vector2.h"
#include "component/component.h"

struct GPLib;
class Entity;

class Lifebar : public Component
{
private:
    Vector2 m_pos;
    Vector2 m_offset;
    float   m_maxLifeState;
    float   m_lifeState;

public:
    Lifebar(Entity&, Vector2 m_offset);
    ~Lifebar() = default;

    GPColor m_lifeColor = { 1.f, 0.f, 0.f, 1.f };
    // BG Size
    float   m_w, m_h;
    // Life bar size
    float   m_lifew, m_lifeh;

    void    update() override;
    void    draw();
};
