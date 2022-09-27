#pragma once

#include "enemy.h"

class Game;

class VeryStrongEnemy : public Enemy
{
private:

public:
    VeryStrongEnemy(Game&, Vector2 pos);
    ~VeryStrongEnemy() = default;

    void    draw() override;
};

