#pragma once

#include "entity.h"
#include "vector2.h"

struct GPLib;
class Life;
class Lifebar;
class BoxCollider;

class Stone : public Entity
{
private:
    Lifebar*        m_lifebar = nullptr;
    BoxCollider*    m_collider = nullptr;
    Sprite          m_sprite;

public:
    Stone(Game&, Vector2 pos);
    ~Stone() = default;

    uint16_t    getLife() const;
    void        updateTexture();


    void    entityDead() override;
    void    collisionHappens(Collider&) override;
    void    draw() override;
};
