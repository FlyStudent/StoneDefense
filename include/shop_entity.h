#pragma once

#include "defines.h"
#include "entity.h"

struct GPLib;
class Game;
class TowerButton;

class ShopEntity : public Entity
{
private:
    //Shop* m_shop;
    TowerButton*  m_standard = nullptr;
    TowerButton*  m_slowing = nullptr;
    TowerButton*  m_explosive = nullptr;
    TowerButton*  m_golden = nullptr;

    uint16_t      m_gold = 0;
    uint16_t      m_totalGold = 0;

public:
    ShopEntity(Game&, uint16_t startGold = START_MONEY);
    ~ShopEntity() = default;

    uint16_t    getGold() const {return m_gold;}
    uint16_t    getTotalGold() const { return m_totalGold; }

    void addGold(uint16_t);
    void subGold(uint16_t);
    void setButton(TowerButton*);
    void activateButton(int towerTag);

    void draw() override;
};
