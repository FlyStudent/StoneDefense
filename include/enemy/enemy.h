#pragma once

#include <vector>

#include "entity.h"
#include "vector2.h"

#include "component/collider.h"


class Life;
class PathFinding;
class BoxCollider;
class Lifebar;
class GoldDealer;

class Enemy : public Entity
{
private:
    std::vector<uint64_t>   m_bulletIDArray;

    // Return true if the given ID is not already saved
    bool        isBulletIDValidate(uint64_t id) const;

protected:
    PathFinding*    m_move = nullptr;
    BoxCollider*    m_collider = nullptr;
    Lifebar*        m_lifebar = nullptr;
    GoldDealer*     m_reward = nullptr;

    bool m_dealGold = false;

    Vector2         m_textureScale = Vector2(1.f, 1.f);
    //EnemyCollisionAttack m_attack = nullptr;
    float           m_damage = 0;

public:
    Enemy(Game& game, Vector2 pos);
    virtual ~Enemy() = default;


    float           getDamage() const {return m_damage;}
    bool            getGoldDeal() const { return m_dealGold; }

    virtual void    entityDead();
    void            collisionHappens(Collider&) override;

    virtual void    draw();
};
