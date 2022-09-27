#include <iostream>
#include <string>
#include <functional>
#include <gp/gp.h>

#include "utility_function.h"

#include "button_entity.h"
#include "shop_entity.h"
#include "castle.h"

#include "component/hide_in_pause.h"

#include "tower/tower_button.h"
#include "tower/standard.h"
#include "tower/slowing.h"
#include "tower/explosive.h"
#include "tower/golden.h"

#include "enemy/enemy_spawn.h"
#include "enemy/weak.h"
#include "enemy/strong.h"
#include "enemy/very_strong.h"
#include "enemy/healer.h"

#include "map.h"
#include "game.h"

Game::Game(GPLib* gp)
: m_gp(gp), m_state(GameState::MENU)
{
    m_collisionEngine = std::make_unique<CollisionEngine>();

    m_ressources =  std::make_unique<Ressources>(this);

    m_inputEngine = std::make_unique<InputEngine>();

    loadTexturesAndSprites();

    goToMenu();
}

void Game::loadTexturesAndSprites()
{
    m_textures.resize(static_cast<size_t>(Texture::COUNT));
    m_textures[(int)Texture::MENU_BACKGROUND] = gpTextureLoadFromFile(m_gp, "resources/menu_background (by Bunifazzuy).png");
    m_textures[(int)Texture::BUTTON_LEVEL1] = gpTextureLoadFromFile(m_gp, "resources/buttons/level1.png");
    m_textures[(int)Texture::BUTTON_LEVEL2] = gpTextureLoadFromFile(m_gp, "resources/buttons/level2.png");
    m_textures[(int)Texture::BUTTON_LEVEL3] = gpTextureLoadFromFile(m_gp, "resources/buttons/level3.png");
    m_textures[(int)Texture::BUTTON_LEVEL4] = gpTextureLoadFromFile(m_gp, "resources/buttons/level4.png");
    m_textures[(int)Texture::BUTTON_LEVEL5] = gpTextureLoadFromFile(m_gp, "resources/buttons/level5.png");
    m_textures[(int)Texture::BUTTON_LEVEL6] = gpTextureLoadFromFile(m_gp, "resources/buttons/level6.png");
    m_textures[(int)Texture::BUTTON_GUIDE] = gpTextureLoadFromFile(m_gp, "resources/buttons/light_bulb.png");
    m_textures[(int)Texture::BUTTON_BACK] = gpTextureLoadFromFile(m_gp, "resources/buttons/menu.png");
    m_textures[(int)Texture::BUTTON_PAUSE] = gpTextureLoadFromFile(m_gp, "resources/buttons/pause.png");
    m_textures[(int)Texture::BUTTON_RESUME] = gpTextureLoadFromFile(m_gp, "resources/buttons/play.png");
    m_textures[(int)Texture::BUTTON_SPEED1] = gpTextureLoadFromFile(m_gp, "resources/buttons/speedup_x1.png");
    m_textures[(int)Texture::BUTTON_SPEED2] = gpTextureLoadFromFile(m_gp, "resources/buttons/speedup_x2.png");
    m_textures[(int)Texture::BUTTON_SPEED3] = gpTextureLoadFromFile(m_gp, "resources/buttons/speedup_x3.png");

    m_sprites.resize(static_cast<size_t>(Sprite::COUNT));
    m_sprites[(int)Sprite::GREEN1] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_42.png");
    m_sprites[(int)Sprite::GREEN2] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_45.png");
    m_sprites[(int)Sprite::GREEN3] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_49.png");
    m_sprites[(int)Sprite::GREEN4] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_57.png");
    m_sprites[(int)Sprite::GREEN_STONE] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_48.png");
    m_sprites[(int)Sprite::WATER1] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_27.png");
    m_sprites[(int)Sprite::WATER2] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_28.png");
    m_sprites[(int)Sprite::SAND] = gpTextureLoadFromFile(m_gp, "resources/tiles/sand_0.png");
    m_sprites[(int)Sprite::DIRT] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_13.png");
    m_sprites[(int)Sprite::ROCK] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_15.png");

    m_sprites[(int)Sprite::ROAD_HORIZONTAL] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_04.png");
    m_sprites[(int)Sprite::ROAD_VERTICAL] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_03.png");
    m_sprites[(int)Sprite::ROAD_CORNER1] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_17.png");
    m_sprites[(int)Sprite::ROAD_CORNER2] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_18.png");
    m_sprites[(int)Sprite::ROAD_CORNER3] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_32.png");
    m_sprites[(int)Sprite::ROAD_CORNER4] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_31.png");
    m_sprites[(int)Sprite::ROAD_CROSS] = gpTextureLoadFromFile(m_gp, "resources/tiles/medievalTile_05.png");

    m_sprites[(int)Sprite::ENEMY_WEAK] = gpTextureLoadFromFile(m_gp, "resources/enemies/weak.png");
    m_sprites[(int)Sprite::ENEMY_HEALER] = gpTextureLoadFromFile(m_gp, "resources/enemies/healer.png");
    m_sprites[(int)Sprite::ENEMY_STRONG] = gpTextureLoadFromFile(m_gp, "resources/enemies/strong.png");
    m_sprites[(int)Sprite::ENEMY_VERY_STRONG1] = gpTextureLoadFromFile(m_gp, "resources/enemies/very_strong_0.png");
    m_sprites[(int)Sprite::ENEMY_VERY_STRONG2] = gpTextureLoadFromFile(m_gp, "resources/enemies/very_strong_1.png");

    m_sprites[(int)Sprite::TOWER_BASE] = gpTextureLoadFromFile(m_gp, "resources/crystal/crystal_base.png");
    m_sprites[(int)Sprite::TOWER_STANDART] = gpTextureLoadFromFile(m_gp, "resources/crystal/crystal_standart.png");
    m_sprites[(int)Sprite::TOWER_SLOW] = gpTextureLoadFromFile(m_gp, "resources/crystal/crystal_slow.png");
    m_sprites[(int)Sprite::TOWER_GOLDEN] = gpTextureLoadFromFile(m_gp, "resources/crystal/crystal_golden.png");
    m_sprites[(int)Sprite::TOWER_EXPLOSIVE] = gpTextureLoadFromFile(m_gp, "resources/crystal/crystal_explosive.png");
    m_sprites[(int)Sprite::TOWER_SPRITESHEET] = gpTextureLoadFromFile(m_gp, "resources/crystal/crystals.png");

    m_sprites[(int)Sprite::CASTLE1] = gpTextureLoadFromFile(m_gp, "resources/castle/castle_1.png");
    m_sprites[(int)Sprite::CASTLE2] = gpTextureLoadFromFile(m_gp, "resources/castle/castle_2.png");
    m_sprites[(int)Sprite::CASTLE3] = gpTextureLoadFromFile(m_gp, "resources/castle/castle_3.png");
    m_sprites[(int)Sprite::CASTLE4] = gpTextureLoadFromFile(m_gp, "resources/castle/castle_4.png");
    m_sprites[(int)Sprite::CASTLE5] = gpTextureLoadFromFile(m_gp, "resources/castle/castle_5.png");

    m_sprites[(int)Sprite::ENEMIES_CASTLE] = gpTextureLoadFromFile(m_gp, "resources/environment/enemies_castle.png");

    m_sprites[(int)Sprite::COIN] = gpTextureLoadFromFile(m_gp, "resources/gold.png");
    m_sprites[(int)Sprite::HEART] = gpTextureLoadFromFile(m_gp, "resources/heart.png");
}


Game::~Game()
{
    clear();

    for (GPTexture text : m_textures)
        gpTextureUnload(m_gp, text);
    for (GPTexture text : m_sprites)
        gpTextureUnload(m_gp, text);
}

Entity*     Game::addEntity(std::unique_ptr<Entity> en)
{
    m_entities.emplace_back(std::move(en));
    m_sortedEntities.emplace_back(m_entities.back().get());
    m_entityCount = m_entities.size();

    return getBackEntity();
}

Entity*     Game::getBackEntity()
{
    return m_entities.back().get();
}

void    Game::setShopButton()
{
    Vector2 towerPos1 = {SCREEN_WIDTH/5, SCREEN_HEIGHT - 50};
    Vector2 towerPos2 = {2*SCREEN_WIDTH/5, SCREEN_HEIGHT - 50};
    Vector2 towerPos3 = {3*SCREEN_WIDTH/5, SCREEN_HEIGHT - 50};
    Vector2 towerPos4 = {4*SCREEN_WIDTH/5, SCREEN_HEIGHT - 50};

    addEntity(std::make_unique<TowerButton>(*this, towerPos1, (int)TowerType::STANDARD));
    TowerButton* curr = reinterpret_cast<TowerButton*>(getBackEntity());
    m_shop->setButton(curr);

    addEntity(std::make_unique<TowerButton>(*this, towerPos2, (int)TowerType::SLOWING));
    curr = reinterpret_cast<TowerButton*>(getBackEntity());
    m_shop->setButton(curr);

    addEntity(std::make_unique<TowerButton>(*this, towerPos3, (int)TowerType::EXPLOSIVE));
    curr = reinterpret_cast<TowerButton*>(getBackEntity());
    m_shop->setButton(curr);

    addEntity(std::make_unique<TowerButton>(*this, towerPos4, (int)TowerType::GOLDEN));
    curr = reinterpret_cast<TowerButton*>(getBackEntity());
    m_shop->setButton(curr);
}

void    Game::setCurrentWave(uint16_t w)
{
    m_wave = w;
}

void  Game::createMainMenu()
{
    Box position = {{SCREEN_WIDTH/8.f, 7.f * SCREEN_HEIGHT/8.f}, 30.f, 30.f };
    std::function<void(void)> event = std::bind(&Game::goToControle, this);
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_GUIDE, event));

    position.m_center.x = 2.f*SCREEN_WIDTH/8.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_1.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL1, event));

    position.m_center.x = 3.f * SCREEN_WIDTH/8.f;
    event = std::bind(&Game::goToLevel, this,"resources/levels/lvl_2.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL2, event));

    position.m_center.x = 4.f * SCREEN_WIDTH / 8.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_3.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL3, event));

    position.m_center.x = 5.f * SCREEN_WIDTH / 8.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_4.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL4, event));

    position.m_center.x = 6.f * SCREEN_WIDTH / 8.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_5.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL5, event));

    position.m_center.x = 7.f * SCREEN_WIDTH / 8.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_6.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL6, event));
}

void  Game::createGuideMenu()
{
    Box position = {{SCREEN_WIDTH/7, 7 * SCREEN_HEIGHT/8}, 30, 30};

    std::function<void(void)> event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_1.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL1, event));

    position.m_center.x = 2.f * SCREEN_WIDTH/ 7.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_2.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL2, event));

    position.m_center.x = 3.f * SCREEN_WIDTH / 7.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_3.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL3, event));

    position.m_center.x = 4.f * SCREEN_WIDTH / 7.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_4.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL4, event));

    position.m_center.x = 5.f * SCREEN_WIDTH / 7.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_5.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL5, event));

    position.m_center.x = 6.f * SCREEN_WIDTH / 7.f;
    event = std::bind(&Game::goToLevel, this, "resources/levels/lvl_6.txt");
    addEntity(std::make_unique<ButtonEntity>(*this, position, Texture::BUTTON_LEVEL6, event));
}

void  Game::createMap(const char* fileName)
{
    m_map = std::make_unique<Map>(fileName);

    addEntity(std::make_unique<Stone>(*this, m_map->m_wayPoints.back()));
    m_castle = reinterpret_cast<Stone*>(getBackEntity());

    createEnemySpawn(m_map->m_wayPoints[0]);

    addEntity(std::make_unique<ShopEntity>(*this, m_startMoney));
    m_shop = reinterpret_cast<ShopEntity*>(getBackEntity());

    setShopButton();
    shopUpdate();

    m_gameCount++;

    m_startTime = gpGetTime(m_gp);

    std::function<void(void)> event = std::bind(&Game::goToPause, this);
    Entity* button = addEntity(std::make_unique<ButtonEntity>(*this, Box{ {SCREEN_WIDTH * 11.f / 12.f, SCREEN_HEIGHT * 0.1f}, 25.f, 25.f }, Texture::BUTTON_PAUSE, event));
    button->addComponent(std::make_unique<HideInPause>(*button))->m_isActivate = true;

    event = std::bind(&Game::updateGameSpeed, this);
    Entity* button2 = addEntity(std::make_unique<ButtonEntity>(*this, Box{ {SCREEN_WIDTH * 11.f / 12.f, SCREEN_HEIGHT * 0.2f }, 25.f, 25.f }, Texture::BUTTON_SPEED1, event));
    button2->addComponent(std::make_unique<HideInPause>(*button2))->m_isActivate = true;
    m_speedButtonTexture = &reinterpret_cast<ButtonEntity*>(button2)->m_texture;
}

void Game::createPause()
{
    std::function<void(void)> event = std::bind(&Game::goBackToLevel, this);
    addEntity(std::make_unique<ButtonEntity>(*this, Box{ {SCREEN_WIDTH / 3.f, SCREEN_HEIGHT * 3.f / 5.f}, 75.f, 75.f }, Texture::BUTTON_RESUME, event));

    event = std::bind(&Game::goToMenu, this);
    addEntity(std::make_unique<ButtonEntity>(*this, Box{ {SCREEN_WIDTH * 2.f / 3.f, SCREEN_HEIGHT * 3.f / 5.f}, 75.f, 75.f }, Texture::BUTTON_BACK, event));
}

Tower*       Game::createTower(int towerTag)
{
    switch(towerTag)
    {
        //Slowing
        case 1 :  
            return  createSlowingTower();
        //Explosive
        case 2 :
            return createExplosiveTower();
        //Golden
        case 3 :
            return createGoldenTower();
        //Standard
        default :
            return createStandardTower();
    }

}


StandardTower*   Game::createStandardTower(Vector2 pos)
{
    addEntity(std::make_unique<StandardTower>(*this, pos));

    return reinterpret_cast<StandardTower*>(getBackEntity());
}

StandardTower*   Game::createStandardTower()
{
    addEntity(std::make_unique<StandardTower>(*this));

    return reinterpret_cast<StandardTower*>(getBackEntity());
}

SlowingTower*  Game::createSlowingTower()
{
    addEntity(std::make_unique<SlowingTower>(*this));

    return reinterpret_cast<SlowingTower*>(getBackEntity());
}

ExplosiveTower*  Game::createExplosiveTower()
{
    addEntity(std::make_unique<ExplosiveTower>(*this));

    return reinterpret_cast<ExplosiveTower*>(getBackEntity());
}

GoldenTower*  Game::createGoldenTower()
{
    addEntity(std::make_unique<GoldenTower>(*this));

    return reinterpret_cast<GoldenTower*>(getBackEntity());
}



EnemySpawn*      Game::createEnemySpawn(Vector2 pos)
{
    addEntity(std::make_unique<EnemySpawn>(*this, pos));

    return reinterpret_cast<EnemySpawn*>(getBackEntity());
}


Enemy*          Game::createEnemy(Vector2 pos, int enemyTag)
{
    switch(enemyTag)
    {
        //Strong
        case 2 :  
            return createStrongEnemy(pos);
        //Healer
        case 3 :
            return createHealerEnemy(pos);
        //very strong (boss)
        case 4 :
            return createVeryStrongEnemy(pos);
        //Weak
        default :
            return  createWeakEnemy(pos);
    }
}

WeakEnemy*      Game::createWeakEnemy(Vector2 pos)
{
    addEntity(std::make_unique<WeakEnemy>(*this, pos));

    return reinterpret_cast<WeakEnemy*>(getBackEntity());
}

StrongEnemy*    Game::createStrongEnemy(Vector2 pos)
{
    addEntity(std::make_unique<StrongEnemy>(*this, pos));

    return reinterpret_cast<StrongEnemy*>(getBackEntity());
}

VeryStrongEnemy*    Game::createVeryStrongEnemy(Vector2 pos)
{
    addEntity(std::make_unique<VeryStrongEnemy>(*this, pos));

    return reinterpret_cast<VeryStrongEnemy*>(getBackEntity());
}

HealerEnemy*    Game::createHealerEnemy(Vector2 pos)
{
    addEntity(std::make_unique<HealerEnemy>(*this, pos));

    return reinterpret_cast<HealerEnemy*>(getBackEntity());
}

void    Game::update()
{
    m_deltaTime = gpGetFrameTime(m_gp) * m_gameSpeed;

    m_inputEngine->update(this);

    switch (m_state)
    {
    case GameState::MENU:
        updateMenu();
        break;
    case GameState::IN_GAME:
        updateInGame();
        break;
    case GameState::GAME_OVER:
        updateGameOver();
        break;
    case GameState::PAUSE:
        updatePause();
        break;
    case GameState::SECRET:
        m_startMoney = 10000;
        updateEntities();
        break;
    case GameState::GUIDE:
        updateEntities();
        break;
    default:
        break;
    }
    destroyKilledEntities();
}

void    Game::updateMenu()
{
    updateEntities();
}

void     Game::updateInGame()
{
    m_mouse->m_selectedTower = nullptr;

    // update difficulty
    m_gameDifficulty = m_shop->getTotalGold() * DIFFICULTY_INCREASE_FACTOR / START_MONEY;

    updateEntities();

    m_collisionEngine->update();

    sortEntities(0, m_entityCount);
}

void Game::updatePause()
{
    updateEntities();
}

void    Game::updateGameOver()
{
    if (m_seconds == 0 && m_minutes == 0)
    {
        float time = gpGetTime(m_gp) - m_startTime;
        m_seconds = utility::getSeconds(time);
        m_minutes = utility::getMinutes(time);
    }
}

void Game::updateEntities()
{
    for (int i = 0; i < m_entities.size(); ++i)
    {
        m_entities[i]->update();
        if (!m_entities[i]->m_isAlive)
        {
            m_eraseList.push_back(i);

        }
    }
}


void    Game::shopUpdate()
{
    switch (m_wave+1)
    {
        case STANDARD_WAVE :
            m_shop->activateButton((int)TowerType::STANDARD);
            break;
        case SLOWING_WAVE :
            m_shop->activateButton((int)TowerType::SLOWING);
            break;
        case EXPLOSIVE_WAVE :
            m_shop->activateButton((int)TowerType::EXPLOSIVE);
            break;
        case GOLDEN_WAVE :
            m_shop->activateButton((int)TowerType::GOLDEN);
        default: break;
    }
}

void    Game::updateGameSpeed()
{
    m_gameSpeed = (int)(m_gameSpeed) % 3 + 1;

    if (m_gameSpeed == 1.f)
        *m_speedButtonTexture = Texture::BUTTON_SPEED1;
    else if (m_gameSpeed == 2.f)
        *m_speedButtonTexture = Texture::BUTTON_SPEED2;
    else
        *m_speedButtonTexture = Texture::BUTTON_SPEED3;
}


void    Game::draw()
{
    switch (m_state)
    {
    case GameState::MENU:
        drawMenu();
        drawEntities();
        break;
    case GameState::GUIDE:
        drawControle();
        drawEntities();
        break;
    case GameState::IN_GAME:
        drawInGame();
        drawEntities();
        break;
    case GameState::PAUSE:
        drawPause();
        break;
    case GameState::SECRET:
        drawSecret();
        drawEntities();
        break;
    case GameState::GAME_OVER:
        drawGameOver();
    default:
        break;
    }
}

void    Game::drawMenu()
{
        gpDrawClearBackground(m_gp, GP_CWHITE);
        gpDrawTextureEx(m_gp, m_textures[(int)Texture::MENU_BACKGROUND], {0.f, 0.f, (float)m_textures[(int)Texture::MENU_BACKGROUND].width, (float)m_textures[(int)Texture::MENU_BACKGROUND].height}, Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0.f, Vector2(1.2f, 1.2f), nullptr, GP_CWHITE);
        gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::BIG_PIXEL], {SCREEN_WIDTH/2, SCREEN_HEIGHT/3}, GP_CBLACK, GP_TEXTALIGN_CENTER, " STONE\nDEFENSE");
        gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {2*SCREEN_WIDTH/5, 2*SCREEN_HEIGHT/3}, GP_CWHITE, GP_TEXTALIGN_CENTER,
         "You have to protect the white square !\nit's a magical stone which give life\nfor each entity of this world, but some bad guys\nare stupid enough to try breaking it." );
/*         if ((int)gpGetTime(m_gp)%3 < 2 && m_gameCount == 0)
            gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/2, 2*SCREEN_HEIGHT/3}, {1.f, 0.f, 0.f, 1.f}, GP_TEXTALIGN_CENTER,
            "\n\n\n\n\n\nPress Space to become a hero");
        else if ((int)(gpGetTime(m_gp)*m_gameCount)%2 < 1 && m_gameCount != 0)
            gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/2, 2*SCREEN_HEIGHT/3}, {1.f, 0.f, 0.f, 1.f}, GP_TEXTALIGN_CENTER,
                "\n\n\n\n\n\n\nPress Space to become a hero (again)");
        gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/2, 2*SCREEN_HEIGHT/3}, {1.f, 0.f, 0.f, 1.f}, GP_TEXTALIGN_CENTER,
                "\n\n\n\n\n\n\n\n\n(or press C to the see the guide)"); */
}

void    Game::drawControle()
{
    gpDrawClearBackground(m_gp, GP_CWHITE);
    gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::BIG_PIXEL], {SCREEN_WIDTH/2, SCREEN_HEIGHT/3}, GP_CBLACK, GP_TEXTALIGN_CENTER, "GUIDE");
    gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/8, SCREEN_HEIGHT*0.45f}, GP_CBLACK, GP_TEXTALIGN_LEFT,
        "- Drag and drop tower with mouse.\
        \n- Beware of your money in the shop, and of your life at the top left.\
        \n- Click on coins on the map to collect bonus money!\
        \n- Drop a tower over another tower to upgrade (1 upgrade by type).\
        \n- 'Speed +' upgrade increases the tower firerate and slow effect.\
        \n- 'Range +' upgrade increases the range and bullet lifetime.\
        \n- 'Gold +' upgrade is useful to earn money by killing enemies.\
        \n- Kill enemies to protect the magic stone.\
        \n- Survive as long as possible!!");

}


void    Game::drawInGame()
{
        if (m_map)
             m_map->draw(m_gp, m_sprites);
}

void Game::drawPause()
{
    if (m_map)
        m_map->draw(m_gp, m_sprites);

    drawEntities();

    gpDrawText(m_gp, m_ressources->m_font[(int)Font::BIG_PIXEL],
        { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3 }, GP_CBLACK, "PAUSE");
}


void    Game::drawGameOver()
{
        if (m_map)
            m_map->draw(m_gp, m_sprites);

        drawEntities();

        gpDrawText(m_gp, m_ressources->m_font[(int)Font::BIG_PIXEL],
                    {SCREEN_WIDTH/4, SCREEN_HEIGHT/3}, GP_CBLACK, "GAME\nOVER");
        drawScore();
        //if ((int)gpGetTime(m_gp)%2 < 1)
        gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/2, 4*SCREEN_WIDTH/5},
                {1.f, 0.f, 0.f, 1.f}, GP_TEXTALIGN_CENTER, "Press Space to go back to menu...");
}
void    Game::drawScore()
{
    gpDrawRectFilled(m_gp, {SCREEN_WIDTH/5, 2*SCREEN_HEIGHT/3, 3*SCREEN_WIDTH/5, SCREEN_WIDTH/4}, utility::colorHexaToFloat(0xAAF3ECB0));
    gpDrawText(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/4, 3*SCREEN_HEIGHT/4}, GP_CBLACK, "Wave : %.1u", m_wave);
    gpDrawText(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/4, 3*SCREEN_HEIGHT/4 + 30}, GP_CBLACK, "Kill : %.1u", m_enemiesKilled);
    gpDrawText(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/2, 3*SCREEN_HEIGHT/4}, GP_CBLACK, "Time : %i min %i s", m_minutes, m_seconds);
    gpDrawText(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], { SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4 + 30 }, GP_CBLACK, "Difficulty : %.2f", m_gameDifficulty);
    gpDrawText(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], { SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4 + 60 }, GP_CBLACK, "Gold : %.1u", m_shop->getTotalGold());
    gpDrawText(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], { SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4 + 90 }, GP_CBLACK, "Tower : %.1u", m_towerCount);
    gpDrawText(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], { SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4 + 90}, GP_CBLACK, "Upgrade : %.1u", m_upgradeCount);
}

void    Game::drawSecret()
{
    gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::BIG_PIXEL], {SCREEN_WIDTH/2, SCREEN_HEIGHT/6}, GP_CWHITE,
        GP_TEXTALIGN_CENTER, "...");
    gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/3, SCREEN_HEIGHT/2}, GP_CWHITE,
        GP_TEXTALIGN_CENTER, "You seems to have lose a lot of time...\nLet me help you !");
    gpDrawTextAligned(m_gp, m_ressources->m_font[(int)Font::LITTLE_PIXEL], {SCREEN_WIDTH/2, 4*SCREEN_HEIGHT/5}, {0.f, 1.f, 0.f, 1.f},
        GP_TEXTALIGN_CENTER, "A mysterious merchand gave you 10000 gold.");
}

void Game::drawEntities()
{
    for (auto& entity : m_sortedEntities)
        if (entity->m_display && entity->m_isAlive)
            entity->draw();
}

void    Game::goToMenu()
{
    clear();
    createMainMenu();
    m_state = GameState::MENU;
}
void    Game::goToControle()
{
    clearEntities();
    createGuideMenu();
    m_state = GameState::GUIDE;
}

void    Game::goToLevel(const char* level)
{
    clearEntities();
    createMap(level);
    m_state = GameState::IN_GAME;
}

void Game::goBackToLevel()
{
    getBackEntity()->m_isAlive = false;
    m_entities[m_entities.size() - 2]->m_isAlive = false;
    m_gameSpeed = 1.f;
    m_state = GameState::IN_GAME;
}

void Game::goToPause()
{
    createPause();
    m_gameSpeed = 0.f;
    m_state = GameState::PAUSE;
}

void    Game::clear()
{
    clearEntities();

    m_wave = 0;
    m_enemiesKilled = 0;
    m_seconds = 0;
    m_minutes = 0;
    m_gameSpeed = 1;
    m_gameDifficulty = 2.f;
}

void    Game::clearEntities()
{
    m_entities.clear();
    m_sortedEntities.clear();
    m_eraseList.clear();
    m_collisionEngine->m_colliders.clear();

    addEntity(std::make_unique<MouseEntity>(*this));
    m_mouse =  reinterpret_cast<MouseEntity*>(getBackEntity());

    m_towerCount = m_upgradeCount = 0;
}

void Game::destroyKilledEntities()
{
    // Destroy entities' smart pointer
    while (m_eraseList.size() > 0)
    {
        int eraseIndex = m_eraseList.back();

        //std::cout << "Destroy entity " << m_entities[eraseIndex].get() << " at index " << eraseIndex << "." << std::endl;

        m_entities.erase(m_entities.begin() + eraseIndex);
        m_eraseList.pop_back();
    }

    m_entityCount = m_entities.size();

    m_sortedEntities.clear();
    for (auto& entity : m_entities)
        m_sortedEntities.emplace_back(entity.get());

    sortEntities(0, m_entityCount);
}

int Game::sortDivide(std::function<bool(Entity*, Entity*)> predicate, int firstIndex, int lastIndex)
{
    if (lastIndex >= m_sortedEntities.size()) return lastIndex;

    Entity* pivot = m_sortedEntities[lastIndex];
    int index = firstIndex;

    for (int i = firstIndex; i < lastIndex; i++)
    {
        Entity* compEntity = m_sortedEntities[i];
        if (
            compEntity->m_layer < pivot->m_layer
            || (compEntity->m_layer == pivot->m_layer && predicate(compEntity, pivot))
            )
        {
            auto temp = m_sortedEntities[i];
            m_sortedEntities[i] = m_sortedEntities[index];
            m_sortedEntities[index] = temp;

            index++;
        }
    }

    auto temp = m_sortedEntities[lastIndex];
    m_sortedEntities[lastIndex] = m_sortedEntities[index];
    m_sortedEntities[index] = temp;

    return index;
}

void Game::sortEntities(int firstIndex, int lastIndex)
{
    if (firstIndex < lastIndex)
    {
        int divide = sortDivide([](Entity* first, Entity* second)->bool {return first->m_pos.y < second->m_pos.y; }, firstIndex, lastIndex);
        sortEntities(firstIndex, divide-1);
        sortEntities(divide+1, lastIndex);
    }
}


