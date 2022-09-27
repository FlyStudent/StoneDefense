#pragma once

#include "vector2.h"
#include "entity.h"

struct GPLib;
class Enemy;
class EnemyWave;

class EnemySpawn : public Entity
{
private:
    EnemyWave*      m_spawn;

public:
    EnemySpawn(Game&, Vector2 pos);
    ~EnemySpawn() = default;

    void    draw();
};
