
#include "game.h"
#include "entity.h"
#include "defines.h"

#include "component/drag_drop.h"

DragDrop::DragDrop(Entity& en)
: Component(en)
{}


void    DragDrop::activeDrag(Entity* en)
{
    m_entityDragged = en;
    m_isActivate = true;
    m_entity.m_game.m_mouse->dragSomething = true;
}

void    DragDrop::update()
{
    auto& entity = m_entityDragged;
    if (!entity->m_game.m_inputEngine->m_mouseLeft)
    {
        entity->entityDropped();
        m_isActivate = false;
        m_entity.m_game.m_mouse->dragSomething = false;
    }
    else
    {
        entity->m_pos = entity->m_game.m_mouse->m_pos;
    }
}

