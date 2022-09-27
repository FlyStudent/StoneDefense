
#include <gp/gp.h>

#include "game.h"
#include "shop_entity.h"
#include "enums.h"
#include "defines.h"
#include "utility_function.h"

#include "tower/slowing.h"
#include "component/circle_collider.h"
#include "component/timer.h"
#include "component/gold_dealer.h"

SlowingTower::SlowingTower(Game& game)
: Tower(game)
{
    m_damage = 5.f;
    m_slowFactor = 0.5f;
    m_price = SLOWING_PRICE;

    Circle circle = {m_pos, 150.f};
    components.emplace_back(std::make_unique<CircleCollider>(*this, circle));
    m_reach = reinterpret_cast<CircleCollider*>(components.back().get());
    m_reach->m_isActivate = false;

    m_reach->setTag((uint64_t)ColliderTag::TOWER_RANGE);
    m_reach->setMask((uint64_t)ColliderTag::ENEMY);

    m_game.m_collisionEngine->setCollider(m_reach);

    components.emplace_back(std::make_unique<Timer>(*this, 2.f));
    m_timer = reinterpret_cast<Timer*>(components.back().get());
    m_timer->m_isActivate = false;

    // goldDealer
    components.emplace_back(std::make_unique<GoldDealer>(*this, m_price));
    m_sold = reinterpret_cast<GoldDealer*>(components.back().get());
    m_sold->m_isActivate = false;

    // Texture
    m_sprite = Sprite::TOWER_SPRITESHEET;
    m_yTextCoordnidate = 40.f;
}


void    SlowingTower::addBullet(Vector2 dir)
{
    if (!m_timer->m_isActivate)
    {
        TowerBullet::TowerBulletConstructorInfo info = { m_pos, dir, m_damage, m_reach->m_circle.m_radius, m_gold, m_bulletDestroyOnCollide, m_slowFactor };
        m_game.addEntity(std::make_unique<TowerBullet>(m_game, *this, info));
        m_timer->startTimer();
    }
}

void    SlowingTower::collisionHappens(Collider& other)
{
    Tower::collisionHappens(other);

    if (other.getTag() == ColliderTag::ENEMY || other.getTag() == ColliderTag::HEALER)
    {
        Vector2 dir = (other.m_entity.m_pos - m_pos).normalize() * 500.f * m_game.getDeltaTime();
        addBullet(dir);
    }
}
