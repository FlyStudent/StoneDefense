
#include <gp/gp.h>

#include "game.h"
#include "defines.h"
#include "utility_function.h"

#include "shop_entity.h"
#include "tower/tower_button.h"

ShopEntity::ShopEntity(Game& game, uint16_t startGold)
: Entity(game, {0, 0}), m_gold(startGold), m_totalGold(startGold)
{
    m_pos = {SCREEN_WIDTH/2, SCREEN_HEIGHT - 50};
}

void ShopEntity::addGold(uint16_t g)
{
    m_gold += g;
    m_totalGold += g;
    m_gold = utility::clamp(m_gold, (uint16_t)0, (uint16_t)10000);
}

void ShopEntity::subGold(uint16_t g)
{
    if (m_gold < g)
        m_gold = 0;
    else
        m_gold -= g;
    
    m_gold = utility::clamp(m_gold, (uint16_t)0, (uint16_t)10000);
}


void ShopEntity::setButton(TowerButton* t)
{
    switch (t->m_towerTag)
    {
        case 1 :
            m_slowing = t;
            break;
        case 2 :
            m_explosive = t;
            break;
        case 3 :
            m_golden = t;
            break;
        default :
            m_standard = t;
            break;
    }
}

void    ShopEntity::activateButton(int towerTag)
{
    switch (towerTag)
    {
        case 1 :
            m_slowing->m_isActivate = true;
            break;
        case 2 :
            m_explosive->m_isActivate = true;
            break;
        case 3 :
            m_golden->m_isActivate = true;
            break;
        default :
            m_standard->m_isActivate = true;
            break;
    }
}


void    ShopEntity::draw()
{
    auto gp = m_game.m_gp;

    const float w = SCREEN_WIDTH/2;
    const float h = 50;
    Box rect = {m_pos, w*0.9, h*0.8};
    gpDrawRectFilled(gp, rect, utility::colorHexaToFloat(0xFFC38B15));

    if (m_game.m_ressources)
        gpDrawText(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL], {m_pos.x - w*0.85f, m_pos.y - 10}, GP_CBLACK, "Money \n%.1u", m_gold);
}