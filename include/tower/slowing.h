#pragma once

#include "tower.h"
#include "bullet.h"

class Game;

class SlowingTower : public Tower
{
private:
    //SlowingTowerAttack*    m_attack = nullptr;

public:
    SlowingTower(Game&);
    ~SlowingTower() = default;

    void    addBullet(Vector2 dir);
    void    addBullet(std::unique_ptr<Entity>&);
    void    collisionHappens(Collider&) override;
};

SlowingTower*    createSlowingTower(Game& game, Vector2 pos);
