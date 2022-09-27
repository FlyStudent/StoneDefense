
#pragma once

#include <gp/gp.h>
#include <string>

class Vector2
{
    private:

    public:
        Vector2();
        Vector2(const float x, const float y);
        Vector2(const Vector2& copy);
        Vector2(const float f);
        Vector2(const GPVector2&);

        ~Vector2();

        float x;
        float y;

        static Vector2 zero;
        static Vector2 up;
        static Vector2 down;
        static Vector2 right;
        static Vector2 left;

        float&  X();
        float&  Y();
        float  X() const;
        float  Y() const;

        Vector2    add(Vector2 v) const;
        Vector2&   add(Vector2 v);

        Vector2    scale(float sc) const;
        Vector2&   scale(float sc);

        Vector2    normalize()const;
        Vector2&   normalize();

        Vector2&    rotate90Degrees();
        Vector2&    rotateMenus90Degrees();

        float   dot_product(Vector2 v) const;
        float   length() const;
        float   cross_product(Vector2 v) const;

        Vector2&   operator=(const Vector2& v);
        Vector2&   operator=(const float f);
        int         operator==(const Vector2& v) const;
        int         operator!=(const Vector2& v) const;
        int         operator<(const Vector2& v) const;
        int         operator<=(const Vector2& v) const;
        int         operator>(const Vector2& v) const;
        int         operator>=(const Vector2& v) const;

        Vector2    operator+(Vector2 v) const;
        Vector2&   operator+=(Vector2 v);
        Vector2    operator-(Vector2 v) const;
        Vector2&   operator-=(Vector2 v);
        Vector2    operator*(float d) const;
        Vector2&   operator*=(float d);
        Vector2    operator/(float d) const;
        Vector2&   operator/=(float d);
        Vector2&   operator++(int i);
        Vector2&   operator--(int i);
        float       operator,(const Vector2 v) const;
        
        float&      operator[](const int i);
        float&      operator[](const char c);
        float&      operator[](const char* str);

        operator GPVector2();
};

Vector2    operator-(const Vector2 v);
Vector2    operator*(const float f, const Vector2 v);
Vector2    operator/(const float f, const Vector2 v);

std::string& operator+(std::string& str, const Vector2& v);
std::string& operator+=(std::string& str, const Vector2& v);
std::ostream& operator<<(std::ostream& stream, const Vector2& v);
Vector2& operator>>(std::istream& stream, Vector2& v);