
#include <gp/gp.h>

#include "enums.h"
#include "defines.h"
#include "entity.h"
#include "game.h"
#include "utility_function.h"

#include "component/enemy_wave.h"
#include "component/timer.h"
#include "component/timerbar.h"

EnemyWave::EnemyWave(Entity& en)
:Component(en)
{
    m_waveTimer.push_back(Timer(en, 20));
    m_waveTimer[0].startTimer();
    m_enemyTimer.push_back(Timer(en, 1));
    m_timerbar.push_back(Timerbar(en, &m_waveTimer[0], -10));
}

int     EnemyWave::randomEneny()
{
    float   strongChance = 0;
    float   healerChance = 0;
    if (m_wave+1 >= STRONG_ENEMY_WAVE)
        strongChance = 10000/5 + utility::clamp((m_wave-STRONG_ENEMY_WAVE), 0, 30)*100;
    if (m_wave+1 >= HEALER_ENEMY_WAVE)
        healerChance = 10000/8 + utility::clamp((m_wave-HEALER_ENEMY_WAVE), 0, 15)*100;

    float   random = rand() % 10000;
    if (0 < random && random < healerChance)
        return 3;
    else if (healerChance < random && random < strongChance+healerChance)
        return 2;
    else
        return 1;
}

void    EnemyWave::update()
{
    m_waveTimer[0].update();
    m_enemyTimer[0].update();
    m_timerbar[0].update();

    if (!m_enemyTimer[0].m_isActivate && m_enemyCount > 0)
    {
        int enemy = randomEneny();

        m_entity.m_game.createEnemy(m_entity.m_pos, enemy);
        m_enemyCount--;
        m_enemyTimer[0].startTimer();
    }
    else if (!m_waveTimer[0].m_isActivate && m_enemyCount <= 0)
    {
        m_wave++;
        m_enemyCount = m_wave + 5;
        m_waveTimer[0].setMaxTimer(m_wave + 20);
        m_waveTimer[0].startTimer();
        m_enemyTimer[0].startTimer();

        m_entity.m_game.setCurrentWave(m_wave);
        m_entity.m_game.shopUpdate();

        //boss pop
        if (m_wave % 10 == 0)
        {
            m_entity.m_game.createEnemy(m_entity.m_pos, 4);
            m_enemyCount = 5;
        }
    }
}

    void    EnemyWave::drawWaveTimerbar()
    {
        m_timerbar[0].draw();
    }
