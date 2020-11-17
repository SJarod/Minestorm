#include <iostream>

#include "myvector2.hpp"

#include "math.hpp"

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

MyVector2 MyVector2::normalizeVect()
{
    MyVector2 nVect;
    float mag = vectorMagnitude();
    return *this / (mag == 0 ? 1 : mag);
}

MyVector2 MyVector2::nullVector()
{
    MyVector2 nullVect;
    nullVect.x = 0.f;
    nullVect.y = 0.f;

    return nullVect;
}

MyVector2 MyVector2::unitVector()
{
    float magnitude = sqrtf(x * x + y * y);
    if (magnitude == 0)
    {
        return nullVector();
    }

    MyVector2 unitVect;
    unitVect.x = x / magnitude;
    unitVect.y = y / magnitude;

    return unitVect;
}

bool MyVector2::equalVector(MyVector2 vector)
{
    float testx = vector.x - x;
    float testy = vector.y - y;

    if (testx >= -FLT_EPSILON && testx <= FLT_EPSILON &&
        testy >= -FLT_EPSILON && testy <= FLT_EPSILON)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float MyVector2::vectorMagnitude()
{
    return sqrtf(x * x + y * y);
}

float MyVector2::vectorSquareMagnitude()
{
    return vectorMagnitude() * vectorMagnitude();
}

float MyVector2::pointsDistance(MyVector2 point)
{
    return sqrtf(powf(x - point.x, 2) + powf(y - point.y, 2));
}

MyVector2 MyVector2::pointsVector(MyVector2 point)
{
    MyVector2 vect;
    vect.x = x - point.x;
    vect.y = y - point.y;

    return vect;
}

MyVector2 MyVector2::addVector(MyVector2 vector)
{
    MyVector2 newVect;
    newVect.x = vector.x + x;
    newVect.y = vector.y + y;

    return newVect;
}

MyVector2 MyVector2::substractVector(MyVector2 vector)
{
    MyVector2 newVect;
    newVect.x = vector.x - x;
    newVect.y = vector.y - y;

    return newVect;
}

MyVector2 MyVector2::scaleVector(float scale)
{
    MyVector2 newVect;
    newVect.x = x * scale;
    newVect.y = y * scale;

    return newVect;
}

MyVector2 MyVector2::negateVector()
{
    return scaleVector(-1);
}

float MyVector2::dotProduct(MyVector2 vector)
{
    return vector.x * x + vector.y * y;
}

float MyVector2::vectorAngle(MyVector2 vector)
{
    float dotProduct    = x * vector.x + y * vector.y;
    float crossProduct  = x * vector.y - y * vector.x;

    return atan2(crossProduct, dotProduct);
}

MyVector2 MyVector2::vectorRotation(float angle)
{
    MyVector2 rvect;
    rvect.x = cosf(angle) * x - sinf(angle) * y;
    rvect.y = sinf(angle) * x + cosf(angle) * y;

    return rvect;
}

MyVector2 MyVector2::vectorRotation90()
{
    return vectorRotation(M_PI / 2);
}

MyVector2 MyVector2::normalVector()
{
    MyVector2 normalVect;

    normalVect.x = -y;
    normalVect.y = x;

    return normalVect;
}

MyVector2 MyVector2::pointRotation(MyVector2 origin, float angle)
{
    MyVector2 rpoint = vectorRotation(angle);
    rpoint.x += origin.x;
    rpoint.y += origin.y;

    return rpoint;
}

bool MyVector2::operator!=(MyVector2 vect) const
{
    return x != vect.x && y != vect.y;
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
    this->x -= vect.x;
    this->y -= vect.y;

    return *this;
}

MyVector2 MyVector2::operator+(MyVector2 vect) const
{
    return MyVector2(x + vect.x, y + vect.y);
}

MyVector2& MyVector2::operator+=(MyVector2 vect)
{
    x += vect.x;
    y += vect.y;

    return *this;
}

MyVector2 MyVector2::operator*(float val) const
{
    return MyVector2(x * val, y * val);
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