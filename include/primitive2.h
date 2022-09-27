#pragma once

#include <iostream>
#include <gp/gp.h>

#include "vector2.h"


struct Primitive2
{
    // Primitive2() = default;
    // Primitive2(const Primitive2&);

    // Primitive2&  operator=(const Primitive2&);
};

struct Range : public Primitive2
{
    Range() = default;
    Range(float min, float max);

    float   m_min;
    float   m_max;
};

struct Box : public Primitive2
{
    Box() = default;
    Box(Vector2 center, float w, float h);
    Box(const Box&);

    Box&    operator=(const Box&);
    operator GPRect();
    
    Vector2 m_center = {0, 0};
    float   m_halfWidth = 0;
    float   m_halfHeight = 0;
};

struct Circle : public Primitive2
{
    Circle() = default;
    Circle(Vector2 center, float radius);
    Circle(const Circle&);

    Circle&    operator=(const Circle&);

    Vector2 m_center;
    float   m_radius;
};

std::ostream&    operator<<(std::ostream&, const Box&);
std::ostream&    operator<<(std::ostream&, const Circle&);

//Range operation
bool    isRangeCollision(Range, Range);

//Vector2 collision
bool	pointBoxCollide(Vector2 pt, Box rect);
bool	pointCircleCollide(Vector2 pt, Circle cir);

//circle collision
bool	circlesCollide(Circle cir1, Circle cir2);
bool	circleBoxCollide(Circle cir, Box rect);

//box collision
bool	boxsCollide(Box rect1, Box rect2);