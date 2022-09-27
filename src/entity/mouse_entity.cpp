
#include <gp/gp.h>

#include "game.h"
#include "enums.h"
#include "tower/tower.h"

#include "mouse_entity.h"
#include "component/mouse_move.h"

MouseEntity::MouseEntity(Game& game)
: Entity(game, {0, 0})
{
    Box box = {m_pos, 1, 1};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::MOUSE);
    m_collider->setMask(ColliderTag::TOWER_SPRITE + ColliderTag::BUTTON);
    
    m_game.m_collisionEngine->setCollider(m_collider);

    components.emplace_back(std::make_unique<MouseMove>(*this));
    m_move = reinterpret_cast<MouseMove*>(components.back().get());
    m_move->m_isActivate = true;
}

void MouseEntity::collisionHappens(Collider& otherCollider)
{
    if (gpMouseButtonIsPressed(m_game.m_gp, GPMouseButton::GP_MOUSE_BUTTON_LEFT))
        otherCollider.m_entity.entityClicked();
}

void    MouseEntity::draw()
{
    //auto gp = m_game.m_gp;
    //gpDrawRectFilled(gp, m_collider->m_box, {1.f, 0.f, 0.f, 1.f});
}
