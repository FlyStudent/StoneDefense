
#include <iostream>
#include <gp/gp.h>

#include "game.h"
#include "enums.h"
#include "utility_function.h"

#include "tower/tower_button.h"
#include "shop_entity.h"
#include "tower/tower.h"
#include "component/timer.h"
#include "component/box_collider.h"
#include "component/circle_collider.h"
#include "component/mouse_move.h"

const Vector2 Tower::m_crystalTextSize = Vector2(35.f, 55.f);


//for test
Tower::Tower(Game& game, Vector2 pos)
: Entity(game, pos)
{
    Box box = {m_pos, (TOWER_SIZE)/2.f, (TOWER_SIZE)/2.f};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::TOWER_SPRITE);
    m_collider->setMask(ColliderTag::TOWER_DRAG + ColliderTag::TOWER_SPRITE + ColliderTag::MOUSE);

    m_game.m_collisionEngine->setCollider(m_collider);

    m_circleColor = utility::colorHexaToFloat(0xFAACCE387);

    m_layer = 5;
}

Tower::Tower(Game& game)
: Entity(game, {-100, 0})
{
    Box box = {m_pos, (TOWER_SIZE)/2, (TOWER_SIZE)/2};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::TOWER_DRAG);
    m_collider->setMask((uint64_t)ColliderTag::TOWER_SPRITE);

    m_game.m_collisionEngine->setCollider(m_collider);

    // components.emplace_back(std::make_unique<MouseMove>(*this, box));
    // m_mouseMove = reinterpret_cast<MouseMove*>(components.back().get());
    // m_mouseMove->m_isActivate = true;

    m_circleColor = utility::colorHexaToFloat(0xF88CCE387);

    m_layer = 5;
}

void    Tower::entityDropped()
{
    if (m_pos.Y() > SCREEN_HEIGHT - 100 || isOnWrongWay())
    {
        m_isAlive = false;
        return;
    }

    m_pos = utility::getTilePosition(m_pos);
    Vector2 tilePos = m_game.m_map->screenToTile(m_pos);

    m_button->m_buyDelayTimer->startTimer();

    m_game.m_shop->subGold(m_price);
    m_game.m_map->placeTowerAt(tilePos.x, tilePos.y + INFO_LINE_NUMBER);
    m_game.m_towerCount++;

    m_collider->m_isActivate = true;
    m_reach->m_isActivate = true;

    m_collider->setTag((uint64_t)ColliderTag::TOWER_SPRITE);
    m_collider->setMask(ColliderTag::TOWER_DRAG + ColliderTag::TOWER_SPRITE + ColliderTag::MOUSE);
    // m_mouseMove->m_isActivate = false;
}

bool    Tower::isOnWrongWay()
{
    auto wrongWay = m_game.m_map->m_noTowerPoint;

    m_pos = utility::getTilePosition(m_pos);

    for (auto way : wrongWay)
    {
        if ((m_pos - way).length() < TILE_SIZE/2)
            return true;
    }
    return false;
}



void    Tower::collisionHappens(Collider& other)
{
    if (m_isAlive == true && m_collider->getTag() == ColliderTag::TOWER_SPRITE && other.getTag() == ColliderTag::TOWER_SPRITE)
    {
        upgradeTower(other);
        other.m_entity.m_isAlive = false;
    }
    if (other.getTag() == ColliderTag::MOUSE && m_game.m_inputEngine->m_mouseLeftPressed)
        m_timer->m_isActivate = false;
    if (other.getTag() == ColliderTag::MOUSE)
    {
        m_circleColor.a = 0.5f;
        m_game.m_mouse->m_selectedTower = this;
    }
}

void    Tower::upgradeTower(Collider& other)
{
    Tower* tower = dynamic_cast<Tower*>(&other.m_entity);
    uint16_t additionalPrice = 0u;

    auto UpdateGameStats = [&]()
    {
        m_game.m_towerCount--;
        m_game.m_upgradeCount++;
    };

    if (tower->getPrice() == SLOWING_PRICE)
    {
        additionalPrice = UPGRADE_PRICE - SLOWING_PRICE;
        if (!m_rangeUp && m_game.m_shop->getGold() >= additionalPrice)
        {
            UpdateGameStats();

            m_rangeUp = true;
            m_reach->m_circle.m_radius *= 1.75f;
            m_bulletDestroyOnCollide = false;
            m_game.m_shop->subGold(additionalPrice);
        }
        else
            m_game.m_shop->addGold(SLOWING_PRICE);
    }
    else if (tower->getPrice() == EXPLOSIVE_PRICE)
    {
        if (!m_damageUp && m_game.m_shop->getGold() >= additionalPrice)
        {
            UpdateGameStats();

            m_damageUp = true;
            m_damage *= 2.f;
            m_game.m_shop->subGold(additionalPrice);
        }
        else
            m_game.m_shop->addGold(EXPLOSIVE_PRICE);
    }
    else if (tower->getPrice() == GOLDEN_PRICE)
    {
        if (!m_gold && m_game.m_shop->getGold() >= additionalPrice)
        {
            UpdateGameStats();
            m_gold = true;
        }
        else
            m_game.m_shop->addGold(GOLDEN_PRICE);
    }
    else
    {
        additionalPrice = UPGRADE_PRICE - STANDARD_PRICE;
        if (!m_speedUp && m_game.m_shop->getGold() >= additionalPrice)
        {
            UpdateGameStats();

            m_speedUp = true;
            m_timer->setMaxTimer(m_timer->getMaxTimer() * 0.5f);

            // Increase slow effect
            if (m_price == SLOWING_PRICE)
                m_slowFactor = 0.25f;

            m_game.m_shop->subGold(additionalPrice);
        }
        else
            m_game.m_shop->addGold(STANDARD_PRICE);
    }
    
}


void    Tower::draw()
{
    auto gp = m_game.m_gp;

    if (m_collider->getTag() == ColliderTag::TOWER_DRAG && !m_game.m_mouse->isOnTower())
        m_circleColor.a = 0.5f;

    if (m_collider->getTag() == ColliderTag::TOWER_DRAG  || !m_game.m_mouse->dragSomething)
    {
        gpDrawCircleFilled(gp, m_pos, m_reach->m_circle.m_radius , m_circleColor);
        m_circleColor.a = m_circleColor.a != 0.f ? 1.f : 0.f;

        gpDrawCircle(gp, m_pos, m_reach->m_circle.m_radius , m_circleColor);
    }
    
    if (m_collider->m_isActivate)
        m_circleColor = utility::colorHexaToFloat(0xF00CCE387);
    else
        m_circleColor.a = 0.5;

    timeElapsed += m_game.getDeltaTime();

    gpDrawTexture(gp, m_game.m_sprites[(int)Sprite::TOWER_BASE], m_pos + Vector2(0.f, 15.f), true, GP_CWHITE);
    float xRectStart = m_firstXTextDistance + ((int)(gpGetTime(gp) * 8.f) % 8 + 1) * (m_crystalTextSize.x + m_xTextDistance);
    gpDrawTextureEx(gp, m_game.m_sprites[(int)m_sprite], {xRectStart, m_yTextCoordnidate, m_crystalTextSize.x, m_crystalTextSize.y}, m_pos - Vector2(0.f, 20.f + sinf(timeElapsed) * 5.f), 0.f, Vector2(1.f, 1.f), nullptr, GP_CWHITE);
}


