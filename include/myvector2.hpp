#pragma once

class MyVector2
{
public:
    float x;
    float y;

    MyVector2();
    MyVector2(float x, float y);

    static const MyVector2 up;
    static const MyVector2 right;
    static const MyVector2 down;
    static const MyVector2 left;

    float       magnitudeVect();
    MyVector2   normalizeVect();

    MyVector2& operator=(MyVector2 vect);
    MyVector2  operator-(MyVector2 vect) const;
    MyVector2& operator-=(MyVector2 vect);
    MyVector2  operator+(MyVector2 vect) const;
    MyVector2& operator+=(MyVector2 vect);
    MyVector2  operator*(float val) const;
    MyVector2& operator*=(float val);
    MyVector2  operator/(float val) const;
    MyVector2& operator/=(float val);
};