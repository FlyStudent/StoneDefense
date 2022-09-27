#pragma once

#include "enemy.h"

class Game;

class WeakEnemy : public Enemy
{
private:

public:
    WeakEnemy(Game&, Vector2 pos);
    ~WeakEnemy() = default;

    void    draw() override;
};
