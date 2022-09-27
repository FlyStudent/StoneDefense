#pragma once

#include "entity.h"
#include "vector2.h"

class Game;
class CircleCollider;
class BoxCollider;
class Timer;
class GoldDealer;
class MouseMove;
class TowerButton;

class Tower : public Entity
{
protected:
    CircleCollider*     m_reach = nullptr;
    BoxCollider*        m_collider= nullptr;   
    GoldDealer*         m_sold = nullptr;

    uint16_t    m_price = 0;
    float       m_damage = 0.f;
    float       m_slowFactor = 1.f;

    bool        m_bulletDestroyOnCollide = true;

    float m_yTextCoordnidate = 0.f;

    float timeElapsed = 0.f;


public:
    static const Vector2 m_crystalTextSize;
    static constexpr float m_xTextDistance = 22.f;
    static constexpr float m_firstXTextDistance = 33.f;

    Tower(Game& game, Vector2 pos);
    Tower(Game& game);
    
    TowerButton*    m_button = nullptr;
    bool            m_gold = false;
    bool            m_damageUp = false;
    bool            m_speedUp = false;
    bool            m_rangeUp = false;
    GPColor         m_circleColor;

    uint16_t        getPrice() {return m_price;}
    float           getDamage() {return m_damage;}
    void            setDamage(uint16_t) {};
    virtual void    entityDropped();
    bool            isOnWrongWay();
    virtual void    collisionHappens(Collider&);
    void            upgradeTower(Collider&);


    virtual void    draw();
};
