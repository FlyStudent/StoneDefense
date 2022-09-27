#pragma once

#include "enemy.h"

class Game;

class StrongEnemy : public Enemy
{
private:

public:
    StrongEnemy(Game&, Vector2 pos);
    ~StrongEnemy() = default;

    void    draw() override;
};

