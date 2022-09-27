
#include <iostream>
#include <string>
#include <cmath>

#include "vector2.h"

Vector2 Vector2::zero(0.f);
Vector2 Vector2::up(0.f, 1.f);
Vector2 Vector2::down(0.f, -1.f);
Vector2 Vector2::right(1.f, 0.f);
Vector2 Vector2::left(-1.f, 0.f);



Vector2::Vector2()
{
    x = 0;
    y = 0;
}

Vector2::Vector2(const float inputX,  const float inputY)
{
    x = inputX;
    y = inputY;
}

Vector2::Vector2(const Vector2& copy)
{
    *this = copy;
}

Vector2::Vector2(const float f)
{
    *this = f;
}

Vector2::Vector2(const GPVector2& v)
{
    x = v.x;
    y = v.y;
}


Vector2::~Vector2()
{
}



Vector2&   Vector2::operator=(const Vector2& v)
{
    x = v.x;
    y = v.y;
    return *this;
}

Vector2&   Vector2::operator=(const float f)
{
    x = f;
    y = f;
    return *this;
}

int         Vector2::operator==(const Vector2& v) const
{
    if (fabsf(x - v.x) < pow(2, -24) && fabsf(y - v.y) < pow(2, -24)) //pow is epsilon
        return 1;
    else
        return 0;
}

int         Vector2::operator!=(const Vector2& v) const
{
    return (*this == v) == 1 ? 0 : 1;
}

int         Vector2::operator<(const Vector2& v) const
{
    return length() < v.length() ? 1 : 0;
}

int         Vector2::operator<=(const Vector2& v) const
{
    return length() <= v.length() ? 1 : 0;
}

int         Vector2::operator>(const Vector2& v) const
{
    return *this <= v ? 0 : 1; 
}

int         Vector2::operator>=(const Vector2& v) const
{
    return *this < v ? 0 : 1; 
}

Vector2    Vector2::operator+(Vector2 v) const
{
    Vector2 vRes(x + v.x, y + v.y);
    return vRes;
}

Vector2&   Vector2::operator+=(Vector2 v)
{
    x += v.x;
    y += v.y;

    return *this;
}

Vector2    Vector2::operator-(Vector2 v) const
{
    Vector2 vRes(x - v.x, y - v.y);
    return vRes;
}

Vector2&   Vector2::operator-=(Vector2 v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

Vector2    operator-(const Vector2 v)
{
    Vector2 vRes(-v.x, -v.y);
    return vRes;
}

Vector2    Vector2::operator*(float f) const
{
    Vector2 vRes(x * f, y * f);
    return vRes;
}

Vector2    operator*(const float f, const Vector2 v)
{
    return v * f;
}

Vector2&   Vector2::operator*=(float f)
{
    *this = *this * f;
    return *this;
}

Vector2    Vector2::operator/(float f) const
{
    Vector2 vRes(x / f, y / f);
    return vRes;  
}

Vector2    operator/(const float f, const Vector2 v)
{
    Vector2 vRes(f / v.x, f / v.y);
    return vRes;
}

Vector2&   Vector2::operator/=(float f)
{
    *this = *this / f;
    return  *this;
}

Vector2&   Vector2::operator++(int i)
{
    float   coef = (length() + 1) / length();
    
    *this = *this * coef;
    return *this;
}

Vector2&   Vector2::operator--(int i)
{
    float   coef = (length() - 1) / length();
    
    *this = *this * coef;
    return *this;
}

float       Vector2::operator,(const Vector2 v) const
{
    return x * v.x + y * v.y;
}


float&      Vector2::operator[](const int i)
{
    if (i == 0)
        return x;
    else
        return y;
}

float&      Vector2::operator[](const char c)
{
    if (c == 'x')
        return x;
    else
        return y;
}

float&      Vector2::operator[](const char* str)
{
    if (str[0] == 'x')
        return x;
    else
        return y;
}




float&      Vector2::X()
{
    return x;
}

float&      Vector2::Y()
{
    return y;
}

float       Vector2::X() const
{
    return x;
}

float       Vector2::Y() const
{
    return y;
}

Vector2    Vector2::add(Vector2 v) const
{
    return *this + v;
}

Vector2&    Vector2::add(Vector2 v)
{
    *this += v;

    return *this;
}

Vector2    Vector2::scale(float sc) const
{
    return *this * sc;
}

Vector2&   Vector2::scale(float sc)
{
    *this *= sc;
    return *this;
}

Vector2    Vector2::normalize() const
{
    return *this / length();
}

Vector2&   Vector2::normalize()
{
    *this = *this / length();
    return *this;
}

Vector2&    Vector2::rotate90Degrees()
{
    float cpy = x;
    x = -y;
    y = cpy;
    return *this;
}

Vector2&    Vector2::rotateMenus90Degrees()
{
    float cpy = x;
    x = y;
    y = -cpy;
    return *this;
}

float       Vector2::dot_product(Vector2 v) const
{
    return (*this,v);  
}

float       Vector2::length() const
{
    return sqrt(x*x + y*y);
}

float       Vector2::cross_product(Vector2 v) const
{
    return x * v.y - y * v.x;
}

Vector2::operator GPVector2()
{
    return {x, y};
}


std::string& operator+(std::string& str, const Vector2& v)
{
    std::string stringX = std::to_string(v.x);
    std::string stringY = std::to_string(v.y);

    str += "x:" + stringX + ",y:" + stringY;

    return str;
}

std::string& operator+=(std::string& str, const Vector2& v)
{
    return str + v;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& v)
{
    return stream << v.x << "," << v.y;
}

Vector2& operator>>(std::istream& stream, Vector2& v)
{
    std::string strX, separator, strY;
    stream >> strX;
    stream >> separator;
    stream >> strY;

    if (separator == ",")
    {
        v.x = ::std::stof(strX);
        v.y = ::std::stof(strY);
    }
    else
    {
        v = Vector2::zero;
    }

    return v;
}

