
#include <gp/gp.h>

#include "game.h"
#include "defines.h"
#include "utility_function.h"
#include "enemy/strong.h"

#include "component/box_collider.h"
#include "component/lifebar.h"
#include "component/life.h"
#include "component/path_finding.h"
#include "component/gold_dealer.h"

StrongEnemy::StrongEnemy(Game& game, Vector2 pos)
: Enemy(game, pos)
{
    m_damage = 10.f;

    //BoxColldier
    Box box = {m_pos, (ENEMY_SIZE)/1.5f, (ENEMY_SIZE)/1.5f};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::ENEMY);
    m_collider->setMask(ColliderTag::TOWER_BULLET + ColliderTag::CASTLE
        + ColliderTag::TOWER_RANGE + ColliderTag::HEALER + ColliderTag::TOWER_EXPLOSION);
    
    m_game.m_collisionEngine->setCollider(m_collider);

    //Life
    float life = 60.f + (float)m_game.getWave() * m_game.getDifficulty();
    components.emplace_back(std::make_unique<Life>(*this, life));
    m_life = reinterpret_cast<Life*>(components.back().get());
    m_life->m_isActivate = true;
    //Move
    components.emplace_back(std::make_unique<PathFinding>(*this, 30u, 5.f));
    m_move = reinterpret_cast<PathFinding*>(components.back().get());
    m_move->m_isActivate = true;
    //Lifebar
    components.emplace_back(std::make_unique<Lifebar>(*this, Vector2(0.f, (ENEMY_SIZE)/2.f + (ENEMY_SIZE)/4.f)));
    m_lifebar = reinterpret_cast<Lifebar*>(components.back().get());
    m_lifebar->m_isActivate = true;
    
   //GoldDealer
    components.emplace_back(std::make_unique<GoldDealer>(*this, STRONG_ENEMY_GOLD));
    m_reward = reinterpret_cast<GoldDealer*>(components.back().get());
    m_reward->m_isActivate = true;

    // Texture
    m_sprite = Sprite::ENEMY_STRONG;
}


void    StrongEnemy::draw()
{
    auto gp = m_game.m_gp;
    Enemy::draw();
}

