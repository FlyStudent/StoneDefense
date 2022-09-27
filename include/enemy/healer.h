#pragma once

#include "enemy.h"

class Game;
class CircleCollider;

class HealerEnemy : public Enemy
{
private:
    CircleCollider* m_healCollider = nullptr;
    uint16_t        m_heal = 0;

//draw variable
    float           m_healAlpha = 0.2f;
    float           m_alphaChange = 0.008f;

public:
    HealerEnemy(Game&, Vector2 pos);
    ~HealerEnemy() = default;

    void    draw() override;
};
