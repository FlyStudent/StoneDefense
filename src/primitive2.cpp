
#include <iostream>

#include "utility_function.h"
#include "primitive2.h"


Range::Range(float min, float max)
:m_min(min), m_max(max) {}

Box::Box(Vector2 center, float w, float h)
:m_center(center), m_halfWidth(w), m_halfHeight(h){}

Box::Box(const Box& b)
: m_center(b.m_center), m_halfWidth(b.m_halfWidth), m_halfHeight(b.m_halfHeight) {}

Box&    Box::operator=(const Box& b)
{
    m_center = b.m_center;
    m_halfWidth = b.m_halfWidth ;
    m_halfHeight = b.m_halfHeight ;
    return *this;
}

Box::operator GPRect()
{
    return {m_center.X() - m_halfWidth, m_center.Y() - m_halfHeight,
        m_halfWidth * 2, m_halfHeight * 2};
}

std::ostream&    operator<<(std::ostream& o, const Box& box)
{
    return o << "Coords : " << box.m_center << " Width : "
            << box.m_halfWidth*2 << " Height : "
            << box.m_halfHeight*2;
}


Circle::Circle(Vector2 center, float radius)
:m_center(center), m_radius(radius){}

Circle::Circle(const Circle& c)
: m_center(c.m_center), m_radius(c.m_radius) {}

Circle&    Circle::operator=(const Circle& c)
{
    m_center = c.m_center;
    m_radius = c.m_radius;
    return *this;
}

std::ostream&    operator<<(std::ostream& o, const Circle& circle)
{
    return o << "Coords : " << circle.m_center << " Radius : "
            << circle.m_radius;
}

bool    isRangeCollision(Range range1, Range range2)
{
    return !((range1.m_min > range2.m_max) || (range2.m_min > range1.m_max));
}

//vector2 collision
bool	pointBoxCollide(Vector2 pt, Box rect)
{
    return (fabsf(pt.x - rect.m_center.x) <= rect.m_halfWidth)
         && (fabsf(pt.y - rect.m_center.y) <= rect.m_halfHeight);
}

bool	pointCircleCollide(Vector2 pt, Circle cir)
{
    return (cir.m_center - pt).length() <= cir.m_radius;
}

//circle collision
bool	circlesCollide(Circle cir1, Circle cir2)
{
    return (cir1.m_radius + cir2.m_radius) >= (cir1.m_center - cir2.m_center).length();
}

bool	circleBoxCollide(Circle cir, Box rect)
{
    if (pointBoxCollide(cir.m_center, rect))
        return true;
    
    Vector2 near_pt;
    near_pt.x = utility::clamp(cir.m_center.x, rect.m_center.x - rect.m_halfWidth,
                        rect.m_center.x + rect.m_halfWidth);
    near_pt.y = utility::clamp(cir.m_center.y, rect.m_center.y - rect.m_halfHeight,
                        rect.m_center.y + rect.m_halfHeight);

    return pointCircleCollide(near_pt, cir);
}

//box collision
bool	boxsCollide(Box rect1, Box rect2)
{
    Range   range1X = {rect1.m_center.x - rect1.m_halfWidth, rect1.m_center.x + rect1.m_halfWidth};
    Range   range1Y = {rect1.m_center.y - rect1.m_halfHeight, rect1.m_center.y + rect1.m_halfHeight};
    Range   range2X = {rect2.m_center.x - rect2.m_halfWidth, rect2.m_center.x + rect2.m_halfWidth};
    Range   range2Y = {rect2.m_center.y - rect2.m_halfHeight, rect2.m_center.y + rect2.m_halfHeight};

    return isRangeCollision(range1X, range2X) && isRangeCollision(range1Y, range2Y);
}

