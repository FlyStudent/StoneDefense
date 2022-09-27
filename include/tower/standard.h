#pragma once

#include <vector>
#include <memory>

#include "tower.h"
#include "bullet.h"

class Game;
class Timer;

class StandardTower : public Tower
{
private:
    //std::vector<std::unique_ptr<TowerBullet>> m_bullets;
    //StandardTowerAttack*    m_attack = nullptr;

public:
    StandardTower(Game& game, Vector2 pos);
    StandardTower(Game& game);
    ~StandardTower() = default;

    void    addBullet(Vector2 dir);
    void    addBullet(std::unique_ptr<Entity>&) {};
    void    collisionHappens(Collider&) override;
};

