
#include <fstream>
#include <iostream>
#include <gp/gp.h>

#include "defines.h"

#include "game.h"
#include "map.h"

Map::Map(const char* fileName)
{
    std::ifstream inputLevel(fileName);

    std::string line;
    while (std::getline(inputLevel, line))
    {
        m_tiles.push_back(line);
    }

    applyDefaultTextures();
    setWallPoints();
    setWayPoints();
}

void    Map::applyDefaultTextures()
{
    m_lineCount = static_cast<int>(m_tiles.size());
    m_columnCount = static_cast<int>(m_tiles[1].size());
    m_tileTexture.resize(m_lineCount * m_columnCount);
    for (int line = INFO_LINE_NUMBER; line < m_lineCount; ++line)
    {
        std::string str = m_tiles[line];

        for (int column = 0; column < m_columnCount; ++column)
        {
            int randomTile = std::rand() % 4;
            Sprite randomSprite = Sprite::NONE;
            switch (randomTile)
            {
            case 1:
                randomSprite = Sprite::GREEN2;
                break;
            case 2:
                randomSprite = Sprite::GREEN3;
                    break;
            case 3:
                randomSprite = Sprite::GREEN4;
                    break;
            default:
                randomSprite = Sprite::GREEN1;
                    break;
            }
            m_tileTexture[line * m_columnCount + column] = randomSprite;
        }
    }
}

inline void applyStoneTexture(char tile, Sprite& texture)
{
    if (tile == '#')
        texture = Sprite::GREEN_STONE;
    else if (tile == 'W')
        texture = Sprite::ROCK;
}

void    Map::setWayPoints()
{
    Vector2 tilePos = findStart();

    m_noTowerPoint.push_back(tileToScreen(tilePos));
    m_wayPoints.push_back(tileToScreen(tilePos));

    Vector2 direction = setDirection();

    char    tile = m_tiles[tilePos.Y()][tilePos.X()];
    while (tile && tile != 'E')
    {
        tilePos.Y() += direction.Y();
        tilePos.X() += direction.X();

        tile = m_tiles[tilePos.Y()][tilePos.X()];
        Sprite& tileTexture = m_tileTexture[tilePos.Y() * m_columnCount + tilePos.X()];
        bool notXMinimum = tilePos.X() > 0;
        bool notXMaximum = tilePos.X() < m_columnCount - 1;
        bool notYMinimum = tilePos.Y() > INFO_LINE_NUMBER;
        bool notYMaximum = tilePos.Y() < m_lineCount - 1;

        switch(tile)
        {
            case 'R':
                // Set Texture
                if (direction == Vector2::up)
                    tileTexture = Sprite::ROAD_CORNER3;
                else if (direction == Vector2::right)
                    tileTexture = Sprite::ROAD_CORNER2;
                else if (direction == Vector2::down)
                    tileTexture = Sprite::ROAD_CORNER1;
                else if (direction == Vector2::left)
                    tileTexture = Sprite::ROAD_CORNER4;

                direction.rotate90Degrees();
                m_wayPoints.push_back(tileToScreen(tilePos));
                break;
            case 'L' :
                // Set Texture
                if (direction == Vector2::up)
                    tileTexture = Sprite::ROAD_CORNER4;
                else if (direction == Vector2::right)
                    tileTexture = Sprite::ROAD_CORNER3;
                else if (direction == Vector2::down)
                    tileTexture = Sprite::ROAD_CORNER2;
                else if (direction == Vector2::left)
                    tileTexture = Sprite::ROAD_CORNER1;

                direction.rotateMenus90Degrees();
                m_wayPoints.push_back(tileToScreen(tilePos));
                break;
            case '+':
                tileTexture = Sprite::ROAD_CROSS;
                break;
            case '-':
                tileTexture = Sprite::ROAD_HORIZONTAL;
                break;
            case '|':
                tileTexture = Sprite::ROAD_VERTICAL;
                break;
            case 'E':
                tileTexture = Sprite::ROCK;

                if (notYMinimum)
                    applyStoneTexture(m_tiles[tilePos.Y() - 1][tilePos.X()], m_tileTexture[(tilePos.Y() - 1) * m_columnCount + tilePos.X()]);
                if (notYMaximum)
                    applyStoneTexture(m_tiles[tilePos.Y() + 1][tilePos.X()], m_tileTexture[(tilePos.Y() + 1) * m_columnCount + tilePos.X()]);
                if (notXMinimum)
                    applyStoneTexture(m_tiles[tilePos.Y()][(tilePos.X() - 1)], m_tileTexture[(tilePos.Y()) * m_columnCount + (tilePos.X() - 1)]);
                if (notXMaximum)
                    applyStoneTexture(m_tiles[tilePos.Y()][(tilePos.X() + 1)], m_tileTexture[(tilePos.Y()) * m_columnCount + (tilePos.X() + 1)]);
                if (notYMinimum && notXMinimum)
                    applyStoneTexture(m_tiles[tilePos.Y() - 1][(tilePos.X() - 1)], m_tileTexture[(tilePos.Y() - 1) * m_columnCount + (tilePos.X() - 1)]);
                if (notYMaximum && notXMinimum)
                    applyStoneTexture(m_tiles[tilePos.Y() + 1][(tilePos.X() - 1)], m_tileTexture[(tilePos.Y() + 1) * m_columnCount + (tilePos.X() - 1)]);
                if (notYMaximum && notXMaximum)
                    applyStoneTexture(m_tiles[tilePos.Y() + 1][(tilePos.X() + 1)], m_tileTexture[(tilePos.Y() + 1) * m_columnCount + (tilePos.X() + 1)]);
                if (notYMinimum && notXMaximum)
                    applyStoneTexture(m_tiles[tilePos.Y() - 1][(tilePos.X() + 1)], m_tileTexture[(tilePos.Y() - 1) * m_columnCount + (tilePos.X() + 1)]);
                break;
            default : 
                break;
        }

        m_noTowerPoint.push_back(tileToScreen(tilePos));
    }

    m_wayPoints.push_back(tileToScreen(tilePos));
    m_noTowerPoint.push_back(tileToScreen(tilePos));

}

void    Map::setWallPoints()
{
    for (int line = INFO_LINE_NUMBER; (line < m_lineCount); ++line)
    {
        std::string str = m_tiles[line];

        for (int column = 0; column < m_columnCount; ++column)
        {
            if (str[column] == 'W')
            {
                m_noTowerPoint.push_back(tileToScreen({(float)column, (float)line}));
                m_tileTexture[line * m_columnCount + column] =Sprite::WATER1;
            }
        }
    }
}


Vector2 Map::findStart()
{
    bool    stopLoop = false;
    Vector2 tilePos = Vector2();

    for (int line = INFO_LINE_NUMBER; (line < m_lineCount) && !stopLoop; ++line)
    {
        std::string str = m_tiles[line];

        for (int column = 0; column < m_columnCount; ++column)
        {
            if (str[column] == 'S')
            {
                tilePos.X() = column;
                tilePos.Y() = line;
                stopLoop = false;
                break;
            }
        }
    }

    return tilePos;
}

Vector2   Map::setDirection()
{
    switch (m_tiles[0][m_tiles[0].length()-1])
    {
        case 'U': return Vector2::down;
        case 'L': return Vector2::left;
        case 'D': return Vector2::up;
        case 'R': ;
        default : return Vector2::right;
    }
}

Vector2   Map::tileToScreen(Vector2 tilePos)
{
    return {tilePos.X() * (TILE_SIZE) + (TILE_SIZE)/2,
         (tilePos.Y() - INFO_LINE_NUMBER) * (TILE_SIZE) + (TILE_SIZE)/2};
}

Vector2   Map::screenToTile(Vector2 screenPos)
{
    return { screenPos.X() / (float)(TILE_SIZE) - 0.5f,
            screenPos.Y() / (float)(TILE_SIZE) - 0.5f};
}

void Map::placeTowerAt(int tileX, int tileY)
{
    Sprite& tileTexture = m_tileTexture[tileY * m_columnCount + tileX];
    bool notXMinimum = tileX > 0;
    bool notXMaximum = tileX < m_columnCount - 1;
    bool notYMinimum = tileY > INFO_LINE_NUMBER;
    bool notYMaximum = tileY < m_lineCount - 1;

    tileTexture = Sprite::DIRT;
    if ((notYMinimum && m_tiles[tileY - 1][tileX] == 'W')
        || (notYMaximum && m_tiles[tileY + 1][tileX] == 'W')
        || (notXMinimum && m_tiles[tileY][tileX - 1] == 'W')
        || (notXMaximum && m_tiles[tileY][tileX + 1] == 'W')
        || (notYMinimum && notXMinimum && m_tiles[tileY - 1][tileX - 1] == 'W')
        || (notYMaximum && notXMinimum && m_tiles[tileY + 1][tileX - 1] == 'W')
        || (notYMaximum && notXMaximum && m_tiles[tileY + 1][tileX + 1] == 'W')
        || (notYMinimum && notXMaximum && m_tiles[tileY - 1][tileX + 1] == 'W'))
        tileTexture = Sprite::SAND;
}


void    Map::draw(GPLib* gp, std::vector<GPTexture> textures)
{
    Vector2 screenPos = Vector2();

    for (int line = INFO_LINE_NUMBER; line < m_lineCount; ++line)
    {
        std::string str = m_tiles[line];

        for (int column = 0; column < m_columnCount; ++column)
        {
            screenPos.X() = (float)column * (TILE_SIZE);
            screenPos.Y() = (float)(line - INFO_LINE_NUMBER) * (TILE_SIZE);
            
            GPTexture texture = textures[(int)m_tileTexture[line * m_columnCount + column]];
            GPRect drawTile = {screenPos.X(), screenPos.Y(), (float)TILE_SIZE, (float)TILE_SIZE};
            gpDrawTextureEx2(gp, texture, { 0.f, 0.f, (float)texture.width, (float)texture.height }, drawTile, GP_CWHITE);
        }
    }
}

void    Map::drawPath(GPLib* gp, std::vector<GPTexture> textures)
{
    int     index = 0;
    Vector2 currentPoint = screenToTile(m_wayPoints[index]);
    Vector2 endPoint = screenToTile(m_wayPoints[index + 1]);
    Vector2 direction= (endPoint - currentPoint).normalize();


    while (index < m_wayPoints.size()-1)
    {
        GPRect rect = {currentPoint.X() * TILE_SIZE, currentPoint.Y() * TILE_SIZE, (float) TILE_SIZE, (float) TILE_SIZE};
        gpDrawRectFilled(gp, rect, {0.7, 0.4, 0.2, 1.0});

        if (currentPoint == endPoint)
        {
            ++index;
            endPoint =  screenToTile(m_wayPoints[index+1]);
            direction= (endPoint - currentPoint).normalize();
        }
        currentPoint += direction;
    }
}

