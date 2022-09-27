#pragma once

#include <vector>
#include <memory>

#include "vector2.h"
#include "primitive2.h"
#include "enums.h"

#include "component/component.h"
#include "component/collider.h"



class Game;
class Life;
class Timer;

class Entity
{
protected:
    std::vector<std::unique_ptr<Component>> components;

    Sprite m_sprite = Sprite::NONE;

public:
    Entity(Game&, Vector2, bool reorder = true);
    virtual ~Entity() = default;

    int         m_layer = 0;
    bool        m_isAlive = true;
    bool        m_display = true;
    Game&       m_game;
    Vector2     m_pos;
    Life*       m_life = nullptr;
    Timer*      m_timer = nullptr;

    virtual void entityDead() {m_isAlive = false;};
    virtual void collisionHappens(Collider&) {};
    virtual void entityClicked() {};
    virtual void entityDropped() {};

    Component*      addComponent(std::unique_ptr<Component> component);  

    void            deactive();
    void            active();

    void            update();
    virtual void    draw();
};


/* template<typename T>
T* Entity::setComponent(T component)
{
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    return reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true; 
} */