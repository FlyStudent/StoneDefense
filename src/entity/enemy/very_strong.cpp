
#include <gp/gp.h>

#include "game.h"
#include "defines.h"
#include "utility_function.h"
#include "enemy/very_strong.h"

#include "component/box_collider.h"
#include "component/lifebar.h"
#include "component/life.h"
#include "component/path_finding.h"
#include "component/gold_dealer.h"

VeryStrongEnemy::VeryStrongEnemy(Game& game, Vector2 pos)
: Enemy(game, pos)
{
    m_damage = 100.f;

    //BoxColldier
    Box box = {m_pos, (ENEMY_SIZE)/1.2f, (ENEMY_SIZE)/1.2f};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::ENEMY);
    m_collider->setMask(ColliderTag::TOWER_BULLET + ColliderTag::CASTLE
        + ColliderTag::TOWER_RANGE + ColliderTag::HEALER + ColliderTag::TOWER_EXPLOSION);
    
    m_game.m_collisionEngine->setCollider(m_collider);

    //Life
    float life = (float)m_game.getWave() * 50.f; 
    components.emplace_back(std::make_unique<Life>(*this, life));
    m_life = reinterpret_cast<Life*>(components.back().get());
    m_life->m_isActivate = true;
    //Move
    components.emplace_back(std::make_unique<PathFinding>(*this, 20u, 5.f));
    m_move = reinterpret_cast<PathFinding*>(components.back().get());
    m_move->m_isActivate = true;
    //Lifebar
    components.emplace_back(std::make_unique<Lifebar>(*this, Vector2(0.f, (ENEMY_SIZE) / 2.f + (ENEMY_SIZE) / 4.f)));
    m_lifebar = reinterpret_cast<Lifebar*>(components.back().get());
    m_lifebar->m_isActivate = true;
    
   //GoldDealer
    components.emplace_back(std::make_unique<GoldDealer>(*this, VERY_STRONG_ENEMY_GOLD));
    m_reward = reinterpret_cast<GoldDealer*>(components.back().get());
    m_reward->m_isActivate = true;

    // Random Texture
    m_sprite = (int)gpGetTime(m_game.m_gp) % 2 == 0 ? Sprite::ENEMY_VERY_STRONG1 : Sprite::ENEMY_VERY_STRONG2;

    m_textureScale = Vector2(2.f, 2.f);
}


void    VeryStrongEnemy::draw()
{
    auto gp = m_game.m_gp;
    Enemy::draw();
}

