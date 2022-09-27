
#include <gp/gp.h>

#include "game.h"
#include "primitive2.h"
#include "enums.h"

#include "enemy/enemy.h"
#include "component/coin_spawner.h"
#include "component/life.h"
#include "component/lifebar.h"
#include "component/box_collider.h"

#include "castle.h"

Stone::Stone(Game& game, Vector2 pos)
: Entity (game, pos)
{
    //down the stone a bit to fix very_strong collision
    m_pos.y += 10;
//collider
    Box box = {m_pos, (CASTLE_SIZE)/2, (CASTLE_SIZE)/2};
    components.emplace_back(std::make_unique<BoxCollider>(*this, box));
    m_collider = reinterpret_cast<BoxCollider*>(components.back().get());
    m_collider->m_isActivate = true;
    
    m_collider->setTag((uint64_t)ColliderTag::CASTLE);
    m_collider->setMask(ColliderTag::ENEMY + ColliderTag::HEALER);

    m_game.m_collisionEngine->setCollider(m_collider);

//life
    components.emplace_back(std::make_unique<Life>(*this, 100.f));
    m_life = reinterpret_cast<Life*>(components.back().get());
    m_life->m_isActivate = true;

//lifebar
    Vector2 upLeftCorner = Vector2(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 20);
    Vector2 offset = upLeftCorner - m_pos;
    m_lifebar = reinterpret_cast<Lifebar*>(addComponent(std::make_unique<Lifebar>(*this, offset)));
    m_lifebar->m_isActivate = true;
    m_lifebar->m_w = TILE_SIZE * 4.f;
    m_lifebar->m_h = TILE_SIZE / 2.f;
    m_lifebar->m_lifew = m_lifebar->m_w * 0.95f;
    m_lifebar->m_lifeh = m_lifebar->m_h * 0.8f;
    m_lifebar->m_lifeColor = { 0.f, 1.f, 0.f, 1.f };

//coin spawner
    addComponent(std::make_unique<CoinSpawner>(*this))->m_isActivate = true;

//texture
    m_layer = 5;
    updateTexture();
}

uint16_t    Stone::getLife() const
{
    return m_life->getLife();
}

void Stone::updateTexture()
{
    float lifeRatio = m_life->getRatio();
    if (lifeRatio < 0.2f)
        m_sprite = Sprite::CASTLE1;
    else if (lifeRatio < 0.4f)
        m_sprite = Sprite::CASTLE2;
    else if (lifeRatio < 0.6f)
        m_sprite = Sprite::CASTLE3;
    else if (lifeRatio < 0.8f)
        m_sprite = Sprite::CASTLE4;
    else
        m_sprite = Sprite::CASTLE5;
}

void    Stone::entityDead()
{
    m_game.m_state = GameState::GAME_OVER;
}

void    Stone::collisionHappens(Collider& other)
{
    if (other.getTag() == ColliderTag::ENEMY)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(&other.m_entity);
        m_life->hurt(enemy->getDamage());
        updateTexture();
    }
}

void Stone::draw()
{
    auto gp = m_game.m_gp;

    gpDrawTexture(gp, m_game.m_sprites[(int)m_sprite], m_collider->m_box.m_center, true,GP_CWHITE);
    
    if (m_lifebar->m_isActivate)
        m_lifebar->draw();
}



