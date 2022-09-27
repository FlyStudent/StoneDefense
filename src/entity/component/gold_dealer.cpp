
#include "game.h"
#include "shop_entity.h"
#include "entity.h"

#include "component/gold_dealer.h"


GoldDealer::GoldDealer(Entity& en, uint16_t gold)
: Component(en), m_goldToDeal(gold)
{}

void    GoldDealer::deal()
{
    m_entity.m_game.m_shop->addGold(m_goldToDeal);
}


void    GoldDealer::update()
{
    //if (!m_entity.m_isAlive)
    //    m_entity.m_game.m_shop->addGold(m_goldToDeal);
}