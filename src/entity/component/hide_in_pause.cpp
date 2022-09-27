
#include "game.h"
#include "entity.h"

#include "component/hide_in_pause.h"

void HideInPause::update()
{
	if (m_entity.m_game.m_state == GameState::PAUSE && m_entity.m_display)
	{
		m_entity.deactive();
		m_isActivate = true;
	}
	else if (m_entity.m_game.m_state != GameState::PAUSE)
		m_entity.active();
}
