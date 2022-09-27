#pragma once

#include "enums.h"
#include "entity.h"
#include "vector2.h"

class Tower;
class Timer;
class Game;
class Button;
class DragDrop;
class BoxCollider;

class TowerButton : public Entity
{
private:
    DragDrop*       m_drag = nullptr;
    BoxCollider*    m_collider = nullptr;
    uint16_t        m_price = 0;


    float           m_animAlpha = 0;
    // Button*         m_button = nullptr;
public:
    TowerButton(Game&, Vector2 pos, int towerTag);
    ~TowerButton() = default;

    Timer*          m_buyDelayTimer = nullptr;
    bool            m_isActivate = false;
    int             m_towerTag = 0;

    void setPrice();

    void collisionHappens(Collider&) override;
    bool isOnWrongWay(Vector2 pos);


    void draw() override;
    void drawDragTile(GPLib*, GPRect);
    // return value depends if tower can be upgraded or not
    bool drawInfo(GPLib*, Vector2, Tower*);
    void drawTower(GPLib*);
    void drawBadClick(GPLib*, GPRect);
};
