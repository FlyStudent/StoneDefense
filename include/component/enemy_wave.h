#pragma once

#include <cstdint>
#include <vector>

#include "component/component.h"

struct GPLib;
class Entity;
class Timer;
class Timerbar;

class EnemyWave : public Component
{
private:
    std::vector<Timer>  m_waveTimer;
    uint16_t            m_wave = 0;
    std::vector<Timer>  m_enemyTimer;
    uint16_t            m_enemyCount = 0;
    std::vector<Timerbar> m_timerbar;

public:
    EnemyWave(Entity&);
    ~EnemyWave() = default;

    int     randomEneny();
    void    update();
    void    drawWaveTimerbar();
};
