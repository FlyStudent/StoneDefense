
#include "game.h"
#include "enums.h"

#include "ressources.h"

Ressources::Ressources(Game* game)
: m_game(game)
{
    m_font.resize((int)Font::COUNT);
    m_font[(int)Font::LITTLE_PIXEL] = gpFontLoad(game->m_gp, "resources/font/mini_pixel-7.ttf", 30);
    m_font[(int)Font::BIG_PIXEL] = gpFontLoad(game->m_gp, "resources/font/light_pixel-7.ttf", 150);

    m_textures.resize((int)Texture::COUNT);
}

Ressources::~Ressources()
{
    for (auto font : m_font)
        gpFontUnload(m_game->m_gp, font);
}