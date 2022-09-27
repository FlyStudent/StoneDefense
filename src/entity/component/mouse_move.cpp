
#include <gp/gp.h>

#include "game.h"
#include "entity.h"

#include "component/mouse_move.h"

MouseMove::MouseMove(Entity& en) : Component(en) {}

void        MouseMove::update()
{
    m_entity.m_pos = gpMousePosition(m_entity.m_game.m_gp);
}