
#include <gp/gp.h>
#include <iostream>

#include "game.h"
#include "shop_entity.h"
#include "enums.h"
#include "defines.h"
#include "utility_function.h"

#include "tower/golden.h"
#include "component/circle_collider.h"
#include "component/timer.h"
#include "component/gold_dealer.h"
#include "component/gold_per_second.h"

GoldenTower::GoldenTower(Game& game)
: Tower(game)
{
    m_damage = 10.f;
    m_price = GOLDEN_PRICE;

    Circle circle = {m_pos, 100.f};
    components.emplace_back(std::make_unique<CircleCollider>(*this, circle));
    m_reach = reinterpret_cast<CircleCollider*>(components.back().get());
    m_reach->m_isActivate = false;

    m_reach->setTag((uint64_t)ColliderTag::TOWER_RANGE);
    m_reach->setMask((uint64_t)ColliderTag::ENEMY);

    m_game.m_collisionEngine->setCollider(m_reach);

//timer
    components.emplace_back(std::make_unique<Timer>(*this, 5.f));
    m_timer = reinterpret_cast<Timer*>(components.back().get());
    m_timer->m_isActivate = false;
//goldDealer
    components.emplace_back(std::make_unique<GoldDealer>(*this, m_price));
    m_sold = reinterpret_cast<GoldDealer*>(components.back().get());
    m_sold->m_isActivate = false;
//goldDealer per second
    components.emplace_back(std::make_unique<GoldPerSecond>(*this, 10u));
    m_dealer = reinterpret_cast<GoldPerSecond*>(components.back().get());
    m_dealer->m_isActivate = false;

    // Texture
    m_sprite = Sprite::TOWER_SPRITESHEET;
    m_yTextCoordnidate = 210.f;
}

void    GoldenTower::entityDropped()
{
    Tower::entityDropped();

    m_reach->m_isActivate = false;
    m_dealer->m_isActivate = true;
}

void    GoldenTower::draw()
{
    auto gp = m_game.m_gp;
    Tower::draw();
    
}



