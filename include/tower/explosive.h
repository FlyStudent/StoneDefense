#pragma once

#include "tower.h"

class Game;
class CircleCollider;
class Timerbar;

class ExplosiveTower : public Tower
{
private:
    //ExplosiveTowerAttack*    m_attack = nullptr;
    CircleCollider*    m_explosion;
    Timerbar*          m_timerbar;     

    float m_shockTime = 1.f;
    float m_currentShockTime = 0.f;

public:
    ExplosiveTower(Game&);
    ~ExplosiveTower() = default;

    // Activate gold dealer or not
    bool    m_explosiveGold = false;

    void    attack();
    void    collisionHappens(Collider&) override;
    void    draw() override;
};

ExplosiveTower*    createExplosiveTower(Game& game, Vector2 pos);