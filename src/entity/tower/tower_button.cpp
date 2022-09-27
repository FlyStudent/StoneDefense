
#include <gp/gp.h>

#include "game.h"
#include "defines.h"
#include "utility_function.h"
#include "primitive2.h"

#include "shop_entity.h"
#include "tower/tower.h"
#include "tower/tower_button.h"
#include "component/button.h"
#include "component/drag_drop.h"
#include "component/timer.h"
#include "component/box_collider.h"

TowerButton::TowerButton(Game& game, Vector2 pos, int towerTag)
: Entity(game, pos), m_towerTag(towerTag)
{
    //in the Entity cstor, they are place by tile, but we don't want that
    m_pos = pos;

    setPrice();

//box
    Box box = {m_pos, TILE_SIZE/2, TILE_SIZE/2};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::BUTTON);
    m_collider->setMask((uint64_t)ColliderTag::MOUSE);

    m_game.m_collisionEngine->setCollider(m_collider);

//Drag and drop
    components.emplace_back(std::make_unique<DragDrop>(*this));
    m_drag = reinterpret_cast<DragDrop*>(components.back().get());
    m_drag->m_isActivate = false;   

    // Timer
    m_buyDelayTimer = reinterpret_cast<Timer*>(addComponent(std::make_unique<Timer>(*this, BUY_DELAY)));

    //texture
    m_layer = 3;
    m_sprite = Sprite::TOWER_SPRITESHEET;
}

void TowerButton::setPrice()
{
    switch (m_towerTag)
    {
        case 1 :
            m_price = SLOWING_PRICE;
            break;
        case 2 :
            m_price = EXPLOSIVE_PRICE;
            break;
        case 3 :
            m_price = GOLDEN_PRICE;
            break;
        default :
            m_price = STANDARD_PRICE;
            break;                    
    }
}

void TowerButton::collisionHappens(Collider& other)
{

    if (m_isActivate && !(*m_buyDelayTimer) && m_drag && !m_drag->m_isActivate && m_price <= m_game.m_shop->getGold())
    {
        if(other.getTag() == ColliderTag::MOUSE && m_game.m_inputEngine->m_mouseLeftPressed)
        {
            m_game.createTower(m_towerTag)->m_button = this;
            Entity* en = reinterpret_cast<Entity*>(m_game.getBackEntity());
            m_drag->activeDrag(en);
        }
    }
    else if (other.getTag() == ColliderTag::MOUSE && m_game.m_inputEngine->m_mouseLeftPressed)
    {
        m_animAlpha = 0.8;
    }
    
}


void TowerButton::draw()
{
    auto gp = m_game.m_gp;

    Box rect = {m_pos, TILE_SIZE/2 *1.2, TILE_SIZE/2 *1.2};
    gpDrawRectFilled(gp, rect, utility::colorHexaToFloat(0xFF76E8C8));

    drawDragTile(gp, rect);
    drawTower(gp);
    drawBadClick(gp, rect);
}

void TowerButton::drawDragTile(GPLib* gp, GPRect rect)
{
    if (m_drag->m_isActivate)
    {
        auto    mouse = m_game.m_mouse;
        auto    mousePos = mouse->m_pos;
        Vector2 dragPos;

        if (mousePos.y < SCREEN_HEIGHT - 100 && !isOnWrongWay(mousePos))
        {
            dragPos = utility::getTilePosition(mousePos);

            Box     dragRect = {dragPos, TILE_SIZE/2, TILE_SIZE/2};

            GPColor color ={0.8f, 0.8f, 0.8f, 0.7f};
            if (mouse->isOnTower())
            {
                color = drawInfo(gp, dragPos, mouse->m_selectedTower) ? GPColor{1.f, 1.f, 0.f, 0.7f} : GPColor{ 1.f, 0.f, 0.f, 0.7f };
            }

            gpDrawRectFilled(gp, dragRect, color);
        }
        else if (isOnWrongWay(mousePos))
        {
            dragPos = utility::getTilePosition(mousePos);

            Box     dragRect = {dragPos, TILE_SIZE/2, TILE_SIZE/2};
            gpDrawRectFilled(gp, dragRect, {1.f, 0.0f, 0.0f, 0.7f});
        }
    }
}

bool TowerButton::drawInfo(GPLib* gp, Vector2 pos, Tower* selected)
{
    Vector2 truePos = {pos.x + (TILE_SIZE * 0.75f), pos.y - TILE_SIZE * 0.5f};
    gpDrawRectFilled(gp, {truePos.x, truePos.y, (TILE_SIZE) * 2, (float)(TILE_SIZE)*0.8f}, utility::colorHexaToFloat(0xFFDFE8B9));
    std::string strPrice = "COST : " + std::to_string(UPGRADE_PRICE);
    switch (m_towerTag)
    {
        case 1 :
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                {truePos.x + 5, truePos.y + 20},   GP_CBLACK, GP_TEXTALIGN_LEFT, "Range +");
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                { truePos.x + 5, truePos.y + 37 }, GP_CBLACK, GP_TEXTALIGN_LEFT, strPrice.c_str());
            return !selected->m_rangeUp;
        case 2 :
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                {truePos.x + 5, truePos.y + 20},  GP_CBLACK, GP_TEXTALIGN_LEFT,"Damage +");
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                { truePos.x + 5, truePos.y + 37 }, GP_CBLACK, GP_TEXTALIGN_LEFT, strPrice.c_str());
            return !selected->m_damageUp;
        case 3 :
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                {truePos.x + 5, truePos.y + 20},  GP_CBLACK, GP_TEXTALIGN_LEFT,"Gold +");
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                { truePos.x + 5, truePos.y + 37 }, GP_CBLACK, GP_TEXTALIGN_LEFT, ("COST : " + std::to_string(GOLDEN_PRICE)).c_str());
            return !selected->m_gold;
        default :
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                {truePos.x + 5, truePos.y + 20},  GP_CBLACK, GP_TEXTALIGN_LEFT, "Speed +");
            gpDrawTextAligned(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL],
                { truePos.x + 5, truePos.y + 37 }, GP_CBLACK, GP_TEXTALIGN_LEFT, strPrice.c_str());
            return !selected->m_speedUp;
    }
}

void TowerButton::drawBadClick(GPLib* gp, GPRect rect)
{
    if (m_animAlpha > 0)
    {
        gpDrawRectFilled(gp, rect, {1.f, 0.f, 0.f, m_animAlpha});
        m_animAlpha -= 0.01;
    }
    else
    {
        m_animAlpha = 0;
    }
    
}


bool    TowerButton::isOnWrongWay(Vector2 pos)
{
    auto wrongWay = m_game.m_map->m_noTowerPoint;

    pos = utility::getTilePosition(pos);

    for (auto way : wrongWay)
    {
        if ((pos - way).length() < TILE_SIZE/2)
            return true;
    }
    return false;
}

void TowerButton::drawTower(GPLib* gp)
{

    unsigned int    price;
    int             wave;
    float           yTextStart = 0.f;

    switch (m_towerTag)
    {
        case 1 :
            yTextStart = 40.f;
            wave = SLOWING_WAVE;
            m_sprite = Sprite::TOWER_SLOW;
            break;
        case 2 :
            yTextStart = 295.f;
            wave = EXPLOSIVE_WAVE;
            m_sprite = Sprite::TOWER_EXPLOSIVE;
            break;
        case 3 :
            yTextStart = 210.f;
            wave = GOLDEN_WAVE;
            m_sprite = Sprite::TOWER_GOLDEN;
            break;
        default :
            yTextStart = 125.f;
            wave = STANDARD_WAVE;
            m_sprite = Sprite::TOWER_STANDART;
            break;
    }

    if (m_isActivate && !(*m_buyDelayTimer))
    {
        gpDrawTexture(gp, m_game.m_sprites[(int)m_sprite], m_pos, true, GP_CWHITE);
        gpDrawText(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL], {m_pos.x + (TILE_SIZE/2)*1.3f, m_pos.y - 10},
             GP_CBLACK, "Cost :\n%.1u", m_price);
    }
    else if (*m_buyDelayTimer)
    {
        float buttonSize = (static_cast<float>(TILE_SIZE) / 2.f) * 1.2f;
        Box rect = { m_pos, buttonSize, buttonSize };


        gpDrawTexture(gp, m_game.m_sprites[(int)m_sprite], m_pos, true, GP_CWHITE);
        gpDrawRectFilled(gp, rect, { 0.2, 0.2, 0.2, 0.7f });
        gpDrawText(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL], { m_pos.x - buttonSize, m_pos.y },
            GP_CBLACK, " %.1f", m_buyDelayTimer->getMaxTimer() - m_buyDelayTimer->getTimer());
    }
    else
    {
        float buttonSize = (static_cast<float>(TILE_SIZE) / 2.f) * 1.2f;
        Box rect = { m_pos, buttonSize, buttonSize };

        gpDrawTexture(gp, m_game.m_sprites[(int)m_sprite], m_pos, true, GP_CWHITE);
        gpDrawRectFilled(gp, rect, {0.2, 0.2, 0.2, 0.7f});
        gpDrawText(gp, m_game.m_ressources->m_font[(int)Font::LITTLE_PIXEL], {m_pos.x - buttonSize, m_pos.y},
                GP_CBLACK, "Wave %.1u", wave);
    }
}


