#pragma once

#include "entity.h"
#include "primitive2.h"
#include "component/box_collider.h"

struct GPLib;
class Game;
class Tower;
class BoxCollider;
class MouseMove;

class MouseEntity : public Entity
{
private:
    BoxCollider*    m_collider;
    MouseMove*      m_move;

public:
    MouseEntity(Game&);
    ~MouseEntity() = default;

    Tower*  m_selectedTower = nullptr;

    bool    isOnTower() const { return m_selectedTower != nullptr; }
    bool    dragSomething = false;

    Box     getBox() const {return m_collider->m_box;}

    void    collisionHappens(Collider& otherCollider) override;
    void    draw() override;
};