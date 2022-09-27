
#include "game.h"
#include "entity.h"

#include "coin_particle.h"

#include "component/gold_per_second.h"

GoldPerSecond::GoldPerSecond(Entity& en, uint16_t gold)
:Component(en)
{
    m_timer.push_back(Timer(en, 1.f));
    m_timer[0].startTimer();
    m_dealer.push_back(GoldDealer(en, gold));
    m_dealer[0].m_isActivate = false;
}

void GoldPerSecond::update()
{
    m_timer[0].update();

    if (!m_timer[0].m_isActivate)
    {
        m_dealer[0].deal();
        m_limit += m_dealer[0].getGold();
        Vector2 randomPosition = Vector2((float)(std::rand() % TILE_SIZE - TILE_SIZE / 2), (float)(std::rand() % TILE_SIZE - TILE_SIZE / 2));
        m_entity.m_game.addEntity(std::make_unique<CoinParticle>(m_entity.m_game, m_entity.m_pos + randomPosition));

        if (m_limit >= GOLDEN_MAX_MONEY)
            m_entity.entityDead();

        m_timer[0].startTimer();
    }
}