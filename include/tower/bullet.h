
#pragma once

#include "entity.h"
#include "primitive2.h"
#include "vector2.h"

class Game;
class Tower;
class BulletMove;
class CircleCollider;

class TowerBullet : public Entity
{
private:
    static uint64_t m_globalID;

    BulletMove*         m_move = nullptr;
    CircleCollider*     m_collider = nullptr;

    float                   m_slow;
    float                   m_damage;
    static constexpr int    m_maxCollision = 3;

public:

    struct TowerBulletConstructorInfo
    {
        Vector2     pos = Vector2::zero;
        Vector2     dir = Vector2::zero;
        float       damage = 1.f;
        float       maxRange = 10.f;
        bool        gold = false;
        bool        destroyOnCollide = true;
        float       slowFactor = 1.f;
    };

    TowerBullet(Game&, Tower&, const TowerBulletConstructorInfo& info);
    ~TowerBullet() = default;

    Tower&  m_tower;
    // Activate gold dealer or not
    bool    m_gold = false;
    bool    m_destroyOnCollide = true;
    int     m_collisionCount = 0;

    uint64_t    m_id = 0;


    float   getSlow() {return m_slow;}
    float   getDamage() {return m_damage;}

    void setMove(const Vector2&);
    void collisionHappens(Collider&) override;
    void entityDead();

    void draw() override;
};
