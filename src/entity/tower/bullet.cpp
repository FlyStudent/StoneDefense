
#include "game.h"
#include "enums.h"
#include "defines.h"
#include "primitive2.h"

#include "tower/tower.h"
#include "tower/bullet.h"
#include "component/bullet_move.h"
#include "component/circle_collider.h"

uint64_t TowerBullet::m_globalID = 0;

TowerBullet::TowerBullet(Game& game, Tower& tower, const TowerBulletConstructorInfo& info)
: Entity(game, info.pos), m_tower(tower), m_slow(info.slowFactor), m_damage(info.damage), m_gold(info.gold), m_destroyOnCollide(info.destroyOnCollide)
{
    m_id = m_globalID++;

    components.emplace_back(std::make_unique<BulletMove>(*this, info.dir, info.maxRange));
    m_move = reinterpret_cast<BulletMove*>(components.back().get());
    m_move->m_isActivate = true;

    Circle circle = {m_pos, BULLET_SIZE};
    components.emplace_back(std::make_unique<CircleCollider>(*this, circle));
    m_collider = reinterpret_cast<CircleCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    m_collider->setTag((uint64_t)ColliderTag::TOWER_BULLET);
    m_collider->setMask(ColliderTag::ENEMY + ColliderTag::HEALER);
    m_game.m_collisionEngine->setWaitingCollider(m_collider);
}

void TowerBullet::collisionHappens(Collider& other)
{
    if (other.getTag() == ColliderTag::ENEMY || other.getTag() == ColliderTag::HEALER)
    {
        if (m_collisionCount > m_maxCollision || m_destroyOnCollide)
            entityDead();
    }
}

void TowerBullet::entityDead()
{
    m_move->m_isActivate = false;
    m_collider->m_isActivate = false;
    m_isAlive = false;
}


void TowerBullet::draw()
{
    auto gp = m_game.m_gp;
    gpDrawCircleFilled(gp, m_pos, (BULLET_SIZE)/2, {1, 0, 1, 1});
}