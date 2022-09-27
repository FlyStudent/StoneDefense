#pragma once

#include <vector>
#include <array>
#include <memory>
#include <functional>

#include "defines.h"
#include "enums.h"

#include "entity.h"
#include "map.h"
#include "collision_engine.h"
#include "input_engine.h"
#include "ressources.h"
#include "mouse_entity.h"



struct GPLib;
class ShopEntity;
class Stone;
class Tower;
class StandardTower;
class SlowingTower;
class ExplosiveTower;
class GoldenTower;
class EnemySpawn;
class Enemy;
class WeakEnemy;
class StrongEnemy;
class VeryStrongEnemy;
class HealerEnemy;

typedef void (*buttonClickedEvent)(void);

class Game
{
private:

    std::vector<std::unique_ptr<Entity>>    m_entities;
    std::vector<Entity*>                    m_sortedEntities;
    std::vector<int>                        m_eraseList;

    float           m_deltaTime;

    float           m_startTime;
    int             m_seconds = 0;
    int             m_minutes = 0;

    uint16_t        m_startMoney = START_MONEY;
    uint16_t        m_wave = 0;
    uint16_t        m_enemiesKilled = 0;
    float           m_gameDifficulty = 2;

    Texture*        m_speedButtonTexture = nullptr;

    void            loadTexturesAndSprites();

    int             sortDivide(std::function<bool(Entity*, Entity*)> predicate, int firstIndex, int lastIndex);

public:
    Game(GPLib* gp);
    ~Game();



    int                     m_gameCount = 0;
    uint16_t                m_towerCount = 0;
    uint16_t                m_upgradeCount = 0;
    uint16_t                m_entityCount = 0;
    float                   m_gameSpeed = 1;
    MouseEntity*            m_mouse = nullptr;
    ShopEntity*             m_shop = nullptr;
    Stone*                  m_castle = nullptr;
    GPLib*                  m_gp = nullptr;
    GameState               m_state = GameState::MENU;

    std::unique_ptr<Map>                m_map = nullptr;
    std::unique_ptr<CollisionEngine>    m_collisionEngine = nullptr;
    std::unique_ptr<InputEngine>        m_inputEngine = nullptr;
    std::unique_ptr<Ressources>         m_ressources = nullptr;

    std::vector<GPTexture>              m_textures;
    std::vector<GPTexture>              m_sprites;

    float           getDeltaTime() const {return m_deltaTime;};
    uint16_t        getWave() const {return m_wave;}
    GPLib*          getGp() const {return m_gp;};
    float           getDifficulty() const {return m_gameDifficulty;}

    Entity*         addEntity(std::unique_ptr<Entity>);
    Entity*         getBackEntity();

    void            enemyKill() {m_enemiesKilled++;}
    void            setShopButton();
    void            setCurrentWave(uint16_t);
    void            setDifficulty(float diff) {m_gameDifficulty *= diff;} 

    void            createMainMenu();
    void            createGuideMenu();
    void            createMap(const char* fileName);
    void            createPause();

    Tower*          createTower(int towerTag);
    StandardTower*  createStandardTower(Vector2 pos);
    StandardTower*  createStandardTower();
    SlowingTower*   createSlowingTower();
    ExplosiveTower* createExplosiveTower();
    GoldenTower*    createGoldenTower();

    EnemySpawn*     createEnemySpawn(Vector2 pos);
    Enemy*          createEnemy(Vector2 pos, int enemyTag);
    WeakEnemy*      createWeakEnemy(Vector2 pos);
    StrongEnemy*    createStrongEnemy(Vector2 pos);
    VeryStrongEnemy* createVeryStrongEnemy(Vector2 pos);
    HealerEnemy*    createHealerEnemy(Vector2 pos);

    void        update();
    void        updateMenu();
    void        updateInGame();
    void        updatePause();
    void        updateGameOver();
    void        updateEntities();
    void        shopUpdate();

    void        updateGameSpeed();

    void        draw();
    void        drawMenu();
    void        drawControle();
    void        drawInGame();
    void        drawPause();
    void        drawGameOver();
    void        drawScore();
    void        drawSecret();
    void        drawEntities();

    void        goToMenu();
    void        goToControle();
    void        goToLevel(const char*);
    void        goBackToLevel();
    void        goToPause();

    void        clear();
    void        clearEntities();
    void        destroyKilledEntities();

    void        sortEntities(int firstIndex, int lastIndex);
};
