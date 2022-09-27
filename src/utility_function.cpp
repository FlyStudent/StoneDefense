
#include <sstream>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <gp/gp.h>

#include "defines.h"
#include "utility_function.h"

GPColor   utility::colorHexaToFloat(uint32_t color)
{
    // colorHexaToFloatWithAlpha(0xFF00FF) => (0x00FF00FF)
    // colorHexaToFloat(0xFF00FF) => (0xFFFF00FF)
    unsigned int alphaMask = 0xFF000000;
    unsigned int redMask   = 0x00FF0000;
    unsigned int greenMask = 0x0000FF00;
    unsigned int blueMask  = 0x000000FF;
    int a = (color & alphaMask) >> 24;
    int r = (color & redMask)   >> 16;
    int g = (color & greenMask) >> 8;
    int b = (color & blueMask)  >> 0;

    return { r / 255.f, g / 255.f, b / 255.f, a / 255.f };
}

Vector2   utility::getTilePosition(Vector2 pos)
{
    pos.x = (int)(pos.x / (TILE_SIZE)) * (TILE_SIZE) + (TILE_SIZE)/2;
    pos.y = (int)(pos.y / (TILE_SIZE)) * (TILE_SIZE) + (TILE_SIZE)/2;
    return pos;
}

int   utility::getMinutes(float time)
{
    return (int)time / 60;
}
int   utility::getSeconds(float time)
{
    return (int)time - getMinutes(time) * 60;
}

