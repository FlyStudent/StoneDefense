#pragma once

#include <string>
#include <vector>

#include "enums.h"
#include "vector2.h"


class GPLib;

class Map
{
private:
    int m_lineCount = 0;
    int m_columnCount = 0;


public:
    Map(const char* fileName);
    ~Map() = default;

    std::vector<std::string>    m_tiles;
    std::vector<Vector2>        m_wayPoints;
    std::vector<Vector2>        m_noTowerPoint;
    std::vector<Sprite>         m_tileTexture;

    void    applyDefaultTextures();
    void    setWayPoints();
    void    setWallPoints();
    Vector2 findStart();
    Vector2 setDirection();
    Vector2 tileToScreen(Vector2);
    Vector2 screenToTile(Vector2);

    void    placeTowerAt(int tileX, int tileY);

    void    draw(GPLib*, std::vector<GPTexture> textures);
    void    drawPath(GPLib* gp, std::vector<GPTexture> textures);
};
