
#include <gp/gp.h>

#include "defines.h"

#include "entity.h"
#include "game.h"
#include "component/life.h"
#include "component/box_collider.h"
#include "component/circle_collider.h"

Entity::Entity(Game& game, Vector2 pos, bool reorder)
: m_game(game), m_pos(pos)
{
    if (reorder)
    {
        m_pos.x = (int)(pos.x / (TILE_SIZE)) * (TILE_SIZE) + (TILE_SIZE)/2;
        m_pos.y = (int)(pos.y / (TILE_SIZE)) * (TILE_SIZE) + (TILE_SIZE)/2;
    }
}

Component* Entity::addComponent(std::unique_ptr<Component> component)
{
    components.emplace_back(std::move(component));
    return components.back().get();
}

void Entity::deactive()
{
    m_display = false;
    for (auto& comp : components)
        comp->m_isActivate = false;
}

void Entity::active()
{
    m_display = true;
    for (auto& comp : components)
        comp->m_isActivate = true;
}

void    Entity::update()
{
    for (auto& component : components)
    {
        if (component && component->m_isActivate)
            component->update();
    }
}



void    Entity::draw()
{
}