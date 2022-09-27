#pragma once

#include <cstdint>

enum class GameState
{
    MENU,
    GUIDE,
    IN_GAME,
    GAME_OVER,
    PAUSE,
    SECRET,

    COUNT
};

enum class Direction
{
    RIGHT,
    UP,
    LEFT,
    DOWN
};

enum class EnemyType
{
    WEAK,
    STRONG,
    HEALER
};

enum class TowerType
{
    STANDARD,
    SLOWING,
    EXPLOSIVE,
    GOLDEN
};

enum class ColliderTag : uint64_t
{
    ENEMY = 1,
    TOWER_RANGE = 2,
    TOWER_BULLET = 4,
    TOWER_SPRITE = 8,
    CASTLE = 16,
    MOUSE = 32,
    HEALER = 64,
    BUTTON = 128,
    TOWER_EXPLOSION = 256,
    TOWER_DRAG = 512,

    NONE = 0
};

enum class Font
{
    LITTLE_PIXEL,
    BIG_PIXEL,

    COUNT
};

/* enum class Image
{
    LANDSCAPE_TILESHEET,

    COUNT
}; */

enum class Texture
{
    NONE,
    LANDSCAPE_TILESHEET,
    MENU_BACKGROUND,
    BUTTON_LEVEL1,
    BUTTON_LEVEL2,
    BUTTON_LEVEL3,
    BUTTON_LEVEL4,
    BUTTON_LEVEL5,
    BUTTON_LEVEL6,
    BUTTON_GUIDE,
    BUTTON_PAUSE,
    BUTTON_RESUME,
    BUTTON_BACK,
    BUTTON_SPEED1,
    BUTTON_SPEED2,
    BUTTON_SPEED3,

    COUNT
};

enum class Sprite
{
    NONE,
    TEXTURE,
    GREEN1,
    GREEN2,
    GREEN3,
    GREEN4,
    GREEN_STONE,
    WATER1,
    WATER2,
    SAND,
    DIRT,
    ROCK,
    ROAD_HORIZONTAL,
    ROAD_VERTICAL,
    ROAD_CORNER1,
    ROAD_CORNER2,
    ROAD_CORNER3,
    ROAD_CORNER4,
    ROAD_CROSS,
    TOWER_BASE,
    TOWER_SPRITESHEET,
    TOWER_STANDART,
    TOWER_SLOW,
    TOWER_GOLDEN,
    TOWER_EXPLOSIVE,
    ENEMY_WEAK,
    ENEMY_HEALER,
    ENEMY_STRONG,
    ENEMY_VERY_STRONG1,
    ENEMY_VERY_STRONG2,
    CASTLE1,
    CASTLE2,
    CASTLE3,
    CASTLE4,
    CASTLE5,
    ENEMIES_CASTLE,
    COIN,
    HEART,
    //etc...
    COUNT
};


uint64_t operator+(ColliderTag a, ColliderTag b);
uint64_t operator+(uint64_t a, ColliderTag b);
uint64_t operator+(ColliderTag b, uint64_t a);
bool operator==(uint64_t a, ColliderTag b);
bool operator==(ColliderTag b, uint64_t a);