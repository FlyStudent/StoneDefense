
#include <gp/gp.h>

#include "game.h"
#include "primitive2.h"

#include "enemy/enemy_spawn.h"
#include "component/enemy_wave.h"

EnemySpawn::EnemySpawn(Game& game, Vector2 pos)
: Entity(game, pos)
{
    components.emplace_back(std::make_unique<EnemyWave>(*this));
    m_spawn = reinterpret_cast<EnemyWave*>(components.back().get());
    m_spawn->m_isActivate = true;
}

void    EnemySpawn::draw()
{
    auto gp = m_game.m_gp;
    gpDrawTexture(gp, m_game.m_sprites[(int)Sprite::ENEMIES_CASTLE], m_pos, true, GP_CWHITE);
    m_spawn->drawWaveTimerbar();
}