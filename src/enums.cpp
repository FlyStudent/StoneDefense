
#include "enums.h"

uint64_t operator+(ColliderTag a, ColliderTag b)
{
    return (uint64_t)a + (uint64_t)b;
}
uint64_t operator+(uint64_t a, ColliderTag b)
{
    return a + (uint64_t)b;
}
uint64_t operator+(ColliderTag b, uint64_t a)
{
    return a + (uint64_t)b;
}
bool operator==(uint64_t a, ColliderTag b)
{
    return a == (uint64_t)b;
}
bool operator==(ColliderTag b, uint64_t a)
{
    return a == (uint64_t)b;
}