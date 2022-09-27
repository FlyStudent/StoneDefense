
#include <gp/gp.h>

#include "game.h"
#include "defines.h"
#include "enemy/healer.h"
#include "utility_function.h"

#include "component/box_collider.h"
#include "component/circle_collider.h"
#include "component/lifebar.h"
#include "component/life.h"
#include "component/path_finding.h"
#include "component/gold_dealer.h"

HealerEnemy::HealerEnemy(Game& game, Vector2 pos)
: Enemy(game, pos)
{
    m_damage = 1.f;

//sprite collider
    Box box = {m_pos, (ENEMY_SIZE)/2.f, (ENEMY_SIZE)/2.f};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::ENEMY);
    m_collider->setMask(ColliderTag::TOWER_BULLET + ColliderTag::HEALER 
        + ColliderTag::CASTLE + ColliderTag::TOWER_RANGE + ColliderTag::TOWER_EXPLOSION);
    
    m_game.m_collisionEngine->setCollider(m_collider);

//heal collider
    Circle circle = {m_pos, (ENEMY_SIZE) * 2.f};
    components.emplace_back(std::make_unique<CircleCollider>(*this, circle));
    m_healCollider = reinterpret_cast<CircleCollider*>(components.back().get());
    m_healCollider->m_isActivate = true;
    
    m_healCollider->setTag((uint64_t)ColliderTag::HEALER);
    m_healCollider->setMask((uint64_t)ColliderTag::ENEMY);
    
    m_game.m_collisionEngine->setCollider(m_healCollider);

//life
    float life = 30.f + (float)m_game.getWave() * m_game.getDifficulty();
    components.emplace_back(std::make_unique<Life>(*this, life));
    m_life = reinterpret_cast<Life*>(components.back().get());
    m_life->m_isActivate = true;
//Lifebar
    components.emplace_back(std::make_unique<Lifebar>(*this, Vector2(0.f, (ENEMY_SIZE) / 2.f + (ENEMY_SIZE) / 4.f)));
    m_lifebar = reinterpret_cast<Lifebar*>(components.back().get());
    m_lifebar->m_isActivate = true;

//move
    components.emplace_back(std::make_unique<PathFinding>(*this, 55u, 10.f));
    m_move = reinterpret_cast<PathFinding*>(components.back().get());
    m_move->m_isActivate = true;

//GoldDealer
    components.emplace_back(std::make_unique<GoldDealer>(*this, HEALER_ENEMY_GOLD));
    m_reward = reinterpret_cast<GoldDealer*>(components.back().get());
    m_reward->m_isActivate = true;

    // Texture
    m_sprite = Sprite::ENEMY_HEALER;
}

void    HealerEnemy::draw()
{
    auto gp = m_game.m_gp;
    Enemy::draw();
    m_alphaChange = m_healAlpha > 0.5f || m_healAlpha < 0.2f ? -m_alphaChange : m_alphaChange;
    m_healAlpha += m_alphaChange;
    gpDrawCircleFilled(gp, m_pos, m_healCollider->m_circle.m_radius, {0.f, 1.f, 0.f, m_healAlpha});
}