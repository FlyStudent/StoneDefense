#pragma once

#include <vector>
#include <gp/gp.h>

class Game;

class Ressources
{
private:
    Game*   m_game;
    
public:
    Ressources(Game*);
    ~Ressources();

    std::vector<GPFont>     m_font;
    std::vector<GPImage>    m_images;
    std::vector<GPTexture>  m_textures;
};
