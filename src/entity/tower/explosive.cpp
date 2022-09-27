#include <gp/gp.h>

#include "game.h"
#include "shop_entity.h"
#include "enums.h"
#include "defines.h"
#include "utility_function.h"

#include "tower/explosive.h"
#include "component/circle_collider.h"
#include "component/timer.h"
#include "component/timerbar.h"
#include "component/gold_dealer.h"


ExplosiveTower::ExplosiveTower(Game& game)
: Tower(game)
{
    m_damage = 15.f;
    m_price = EXPLOSIVE_PRICE;

//tower range
    Circle circle = {m_pos, 60.f};
    components.emplace_back(std::make_unique<CircleCollider>(*this, circle));
    m_reach = reinterpret_cast<CircleCollider*>(components.back().get());
    m_reach->m_isActivate = false;

    m_reach->setTag((uint64_t)ColliderTag::TOWER_RANGE);
    m_reach->setMask((uint64_t)ColliderTag::ENEMY);

    m_game.m_collisionEngine->setCollider(m_reach);


//tower explosion
    components.emplace_back(std::make_unique<CircleCollider>(*this, circle));
    m_explosion = reinterpret_cast<CircleCollider*>(components.back().get());
    m_explosion->m_isActivate = false;

    m_explosion->setTag((uint64_t)ColliderTag::TOWER_EXPLOSION);
    m_explosion->setMask((uint64_t)ColliderTag::ENEMY);

    m_game.m_collisionEngine->setCollider(m_explosion);

//timer
    components.emplace_back(std::make_unique<Timer>(*this, 5.f));
    m_timer = reinterpret_cast<Timer*>(components.back().get());
    m_timer->m_isActivate = false;

    m_currentShockTime = m_shockTime;

//timerbar
    components.emplace_back(std::make_unique<Timerbar>(*this, nullptr, 20.f));
    m_timerbar = reinterpret_cast<Timerbar*>(components.back().get());
    m_timerbar->m_isActivate = true;

//goldDealer
    components.emplace_back(std::make_unique<GoldDealer>(*this, m_price));
    m_sold = reinterpret_cast<GoldDealer*>(components.back().get());
    m_sold->m_isActivate = false;

    // Texture
    m_sprite = Sprite::TOWER_SPRITESHEET;
    m_yTextCoordnidate = 295.f;
}



void    ExplosiveTower::attack()
{
    m_explosiveGold = m_gold;
    if (!m_timer->m_isActivate)
    {
        m_explosion->m_isActivate = true;
        m_timer->startTimer();
        m_currentShockTime = 0.f;
    }
    else if (m_currentShockTime >= 0.f + m_game.getDeltaTime())
    {
        m_explosion->m_isActivate = false;
    }
}

void    ExplosiveTower::collisionHappens(Collider& other)
{
    Tower::collisionHappens(other);

    m_explosion->m_circle.m_radius = m_reach->m_circle.m_radius;

    if (other.getTag() == ColliderTag::ENEMY)
        attack();
}

void    ExplosiveTower::draw()
{
    auto gp = m_game.m_gp;

    Tower::draw();
    
    m_currentShockTime += m_game.getDeltaTime();;
    float shockTimeRatio = m_currentShockTime / m_shockTime;
    gpDrawCircleFilled(gp, m_pos, m_reach->m_circle.m_radius, { 1.f, 0.2f, 0.2f, 1.f - shockTimeRatio });

    if (m_timer->getTimer() < m_timer->getMaxTimer())
        m_timerbar->draw();
}
