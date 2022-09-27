
#include "entity.h"
#include "mouse_entity.h"

#include "component/button.h"
#include "component/box_collider.h"

    
Button::Button(Entity& en, Box box, std::function<void(void)> event)
: Component(en), m_event(event)
{
    m_collider = std::make_unique<BoxCollider>(en, box);
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::BUTTON);
    m_collider->setMask((uint64_t)ColliderTag::MOUSE);
}

void    Button::update()
{
    m_collider->m_box.m_center = m_entity.m_pos;

    if (!m_collider->m_isActivate)
        return;


    auto& mouse = m_entity.m_game.m_mouse;
    auto& input = m_entity.m_game.m_inputEngine;

    isOverlapped = boxsCollide(mouse->getBox(), m_collider->m_box);

    if (input->m_mouseLeftPressed && isOverlapped)
        m_event();
}