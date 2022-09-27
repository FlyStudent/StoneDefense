
#include <gp/gp.h>
#include <iostream>

#include "game.h"
#include "enums.h"
#include "input_engine.h"
#include "utility_function.h"

void    InputEngine::update(Game* game)
{
    //GP_API bool gpKeyIsPressed(GPLib* gp, GPKey key);
    // GP_API bool gpKeyIsDown(GPLib* gp, GPKey key);
    // GP_API bool gpKeyIsUp(GPLib* gp, GPKey key);
    // GP_API bool gpKeyIsReleased(GPLib* gp, GPKey key);

    changeGameState(game);

    auto mousePos =  game->m_mouse->m_pos;

    if (gpMouseButtonIsDown(game->m_gp, GP_MOUSE_BUTTON_2))
        m_mouseRight = true;
    else if (gpMouseButtonIsUp(game->m_gp, GP_MOUSE_BUTTON_2))
        m_mouseRight = false;

    if (gpMouseButtonIsPressed(game->m_gp, GP_MOUSE_BUTTON_2))
    {
        game->createWeakEnemy(game->m_map->m_wayPoints[0]);
        m_mouseRightPressed = true;
    }
    else
    {
        m_mouseRightPressed = false;
    }

    if (gpMouseButtonIsDown(game->m_gp, GP_MOUSE_BUTTON_1))
        m_mouseLeft = true;
    else if (gpMouseButtonIsUp(game->m_gp, GP_MOUSE_BUTTON_1))
        m_mouseLeft = false;

    if (gpMouseButtonIsPressed(game->m_gp, GP_MOUSE_BUTTON_1))
    {
/*         if (mousePos.Y() < SCREEN_HEIGHT - 100)
            game->createStandardTower({mousePos.X(), mousePos.Y()}); */
        m_mouseLeftPressed = true;
    }
    else
    {
        m_mouseLeftPressed = false;
    }
}

void    InputEngine::changeGameState(Game* game)
{
    if (gpKeyIsPressed(game->m_gp, GP_KEY_SPACE) && game->m_state == GameState::MENU && game->m_gameCount == 7)
        game->m_state = GameState::SECRET;
    else if (gpKeyIsPressed(game->m_gp, GP_KEY_SPACE) && game->m_state == GameState::GAME_OVER)
    {
        game->goToMenu();
    }

    if (gpKeyIsPressed(game->m_gp, GP_KEY_C) && game->m_state == GameState::MENU)
        game->m_state = GameState::GUIDE;
}
