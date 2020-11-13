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

    //return a null vector
    MyVector2 nullVector();

    //return a unit vector, normalized vector
    MyVector2 unitVector();

    //vector equality check to near epsilon
    bool equalVector(MyVector2 vector);

    //return vector magnitude (length)
    float vectorMagnitude();

    //return vector square magnitude
    float vectorSquareMagnitude();

    //return distance between two points
    float pointsDistance(MyVector2 point);

    //return vector between two points
    MyVector2 pointsVector(MyVector2 point);

    //return merged vector
    MyVector2 addVector(MyVector2 vector);
    MyVector2 substractVector(MyVector2 vector);

    //return vector multiplied by scale
    MyVector2 scaleVector(float scale);

    //return negate vector
    MyVector2 negateVector();

    //dot product of 2 vectors
    float dotProduct(MyVector2 vector);

    //return angle between 2 vectors
    float vectorAngle(MyVector2 vector);

    //returns vector's rotation
    MyVector2 vectorRotation(float angle);
    MyVector2 vectorRotation90();
    MyVector2 normalVector();

    //returns point's rotation arround a given point
    MyVector2 pointRotation(MyVector2 origin, float angle);

    bool       operator!=(MyVector2 vect) const;

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