
#include <iostream>

#include "game.h"
#include "entity.h"
#include "component/path_finding.h"

PathFinding::PathFinding(Entity& en, uint16_t speed, float range)
: Component(en), m_speed(speed), m_originalSpeed(speed), m_range(range)
{
    m_wayPointNb = 1;
    m_nextPoint = m_entity.m_game.m_map->m_wayPoints[m_wayPointNb];
    m_dirVector = (m_nextPoint - m_entity.m_pos).normalize() * m_speed * m_entity.m_game.getDeltaTime();

    m_speedTimer.push_back(Timer(en, 6));
    m_speedTimer[0].m_isActivate = false;
}

void PathFinding::setSpeed(float scaler)
{
    if (scaler != 1.f && !m_speedTimer[0].m_isActivate)
    {
        m_speed = m_originalSpeed * scaler;
        m_speedTimer[0].startTimer();
    }
}


void    PathFinding::update()
{
    m_entity.m_pos += m_dirVector;

    m_speedTimer[0].update();
    
    if (m_speed != m_originalSpeed && !m_speedTimer[0].m_isActivate)
        m_speed = m_originalSpeed;

    assertGoal();
}


void    PathFinding::assertGoal()
{
    auto  gameSpeed = m_entity.m_game.m_gameSpeed;
    auto& wayPoints = m_entity.m_game.m_map->m_wayPoints;
    //Change wayPoint if needed
    if ((m_nextPoint - m_entity.m_pos).length() < (m_range + (gameSpeed/2)))
    {
        m_wayPointNb = m_wayPointNb++ >= wayPoints.size()-1 ? 0 : m_wayPointNb;

        m_nextPoint = wayPoints[m_wayPointNb];
    }

    m_dirVector = ((m_nextPoint - m_entity.m_pos).normalize()) * m_speed * m_entity.m_game.getDeltaTime();      

}