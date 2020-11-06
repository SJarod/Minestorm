#include "myvector2.hpp"

#include <cmath>

const MyVector2 MyVector2::up(0.f, -1.f);
const MyVector2 MyVector2::right(1.f, 0.f);
const MyVector2 MyVector2::down(0.f, 1.f);
const MyVector2 MyVector2::left(-1.f, 0.f);

MyVector2::MyVector2()
{
    x = 0;
    y = 0;
}

MyVector2::MyVector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float MyVector2::magnitudeVect()
{
    return sqrtf(x * x + y * y);
}

MyVector2 MyVector2::normalizeVect()
{
    MyVector2 nVect;
    float mag = magnitudeVect();
    return *this / (mag == 0 ? 1 : mag);
}

MyVector2& MyVector2::operator=(MyVector2 vect)
{
    this->x = vect.x;
    this->y = vect.y;

    return *this;
}

MyVector2 MyVector2::operator-(MyVector2 vect) const
{
    return MyVector2(x - vect.x, y - vect.y);
}

MyVector2& MyVector2::operator-=(MyVector2 vect)
{
    return *this;
}

MyVector2 MyVector2::operator+(MyVector2 vect) const
{
    return *this;
}

MyVector2& MyVector2::operator+=(MyVector2 vect)
{
    return *this;
}

MyVector2 MyVector2::operator*(float val) const
{
    return *this;
}

MyVector2& MyVector2::operator*=(float val)
{
    return *this;
}

MyVector2 MyVector2::operator/(float val) const
{
    return MyVector2(x / val, y / val);
}

MyVector2& MyVector2::operator/=(float val)
{
    return *this;
}