
#include <gp/gp.h>
#include <iostream>

#include "game.h"
#include "enums.h"

#include "entity.h"
#include "coin_particle.h"
#include "enemy/enemy.h"
#include "tower/tower.h"
#include "tower/explosive.h"
#include "tower/bullet.h"

#include "component/life.h"
#include "component/lifebar.h"
#include "component/gold_dealer.h"
#include "component/path_finding.h"
#include "component/box_collider.h"
#include "component/circle_collider.h"


bool Enemy::isBulletIDValidate(uint64_t id) const
{
    for (uint64_t otherID : m_bulletIDArray)
    {
        if (id == otherID)
            return false;
    }

    return true;
}

Enemy::Enemy(Game& game, Vector2 pos)
:Entity(game, pos)
{
    m_layer = 5;
}

void    Enemy::entityDead()
{
    m_game.enemyKill();

    if (m_dealGold)
    {
        m_reward->deal();
        m_game.addEntity(std::make_unique<CoinParticle>(m_game, m_pos));
    }

    m_isAlive = false;
}

void    Enemy::collisionHappens(Collider& other)
{
    auto tag = other.getTag();

    if (tag == ColliderTag::TOWER_BULLET)
    {
        TowerBullet* bullet = dynamic_cast<TowerBullet*>(&other.m_entity);

        if (isBulletIDValidate(bullet->m_id))
        {
            m_dealGold = bullet->m_gold;
            m_life->hurt(bullet->getDamage());
            m_move->setSpeed(bullet->getSlow());
            bullet->m_collisionCount++;

            if (static_cast<int>(m_bulletIDArray.size()) >= 30)
                m_bulletIDArray.erase(m_bulletIDArray.begin());

            m_bulletIDArray.push_back(bullet->m_id);
        }
    }
    else if (tag == ColliderTag::TOWER_EXPLOSION)
    {
        ExplosiveTower* tower = dynamic_cast<ExplosiveTower*>(&other.m_entity);
        m_dealGold = tower->m_explosiveGold;
        m_life->hurt(tower->getDamage());
    }
    else if (tag == ColliderTag::CASTLE)
    {
        entityDead();
        m_dealGold = true;
    }
    else if(tag == ColliderTag::HEALER)
    {
        m_life->heal(m_game.getWave()/100);
    }
}

void    Enemy::draw()
{
    if (!m_isAlive)
        return;

    auto gp = m_game.m_gp;
    if (m_lifebar->m_isActivate)
        m_lifebar->draw();
    // Draw texture and move it to procude a simple effect
    Vector2 drawPos = m_pos + Vector2(0.f, (int)(gpGetTime(gp) * 2.f) % 2 == 0 ? 5.f : 0.f);
    GPTexture sprite = m_game.m_sprites[(int)m_sprite];
    gpDrawTextureEx(gp, sprite, {0.f, 0.f, (float)sprite.width, (float)sprite.height}, drawPos, 0.f, m_textureScale, nullptr, GP_CWHITE);
}




