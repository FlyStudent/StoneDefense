#pragma once

#include <string>
#include <cstdint>
#include <gp/gp.h>

#include "vector2.h"

namespace utility
{
    template<typename T>
    T   clamp(T x, T min, T max)
    {
        x = x < min ? min : x;
        return x > max ? max : x;
    }

    GPColor     colorHexaToFloat(uint32_t color);
    Vector2     getTilePosition(Vector2);

    int         getMinutes(float time);
    int         getSeconds(float time);
}

