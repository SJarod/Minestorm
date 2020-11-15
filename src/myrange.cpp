#include "myrange.hpp"

#include "myvector2.hpp"
#include "myrectangle.hpp"
#include "mycircle.hpp"

#include "math.hpp"

void MyRange::rangeInit(float value)
{
    min = value;
    max = value;
}

MyRange MyRange::mergeRange(MyRange range)
{
    MyRange newRange;

    if (min <= range.min)
        newRange.min = min;
    else
        newRange.min = range.min;

    if (max >= range.max)
        newRange.max = max;
    else
        newRange.max = range.max;

    return newRange;
}

void MyRange::rangeAddValue(float value)
{
    if (value <= min)
    {
        min = value;
    }
    else
    {
        min = min;
    }

    if (value >= max)
    {
        max = value;
    }
    else
    {
        max = max;
    }
}

bool MyRange::rangeCollision(MyRange range)
{
    if (min < range.min)
    {
        return range.min <= max;
    }
    else if (range.min < min)
    {
        return min <= range.max;
    }
    else
    {
        return min == range.min;
    }
}

MyRange MyRange::rangePoint(MyVector2 point, MyVector2 dir)
{
    MyRange newRange;
    
    newRange.min = point.dotProduct(dir);
    newRange.max = newRange.min;

    return newRange;
}

MyRange MyRange::rangeRectangle(MyRectangle rect, MyVector2 dir)
{
    MyRange newRange;
    MyVector2 A, B, C, D;   //4 corners of rectangle
    float a, b, c, d;       //dotProduct

    A.x = rect.center.x - rect.width / 2;
    A.y = rect.center.x - rect.height / 2;
    a = A.dotProduct(dir);

    B.x = rect.center.x + rect.width / 2;
    B.y = rect.center.x - rect.height / 2;
    b = B.dotProduct(dir);

    C.x = rect.center.x - rect.width / 2;
    C.y = rect.center.x + rect.height / 2;
    c = C.dotProduct(dir);

    D.x = rect.center.x + rect.width / 2;
    D.y = rect.center.x + rect.height / 2;
    d = D.dotProduct(dir);

    newRange.min = Math::min(Math::min(a, b), Math::min(c, d));
    newRange.max = Math::max(Math::max(a, b), Math::max(c, d));

    return newRange;
}

MyRange MyRange::rangeCircle(MyCircle circle, MyVector2 dir)
{
    MyRange newRange;
    MyVector2 A, B;     //2 points of circle
    float angle;

    A.x = circle.center.x - circle.radius;
    A.y = circle.center.y;
    B.x = circle.center.x + circle.radius;
    B.y = circle.center.y;

    angle = dir.vectorAngle(A.pointsVector(B));
    A = A.pointRotation(circle.center, angle);
    B = B.pointRotation(circle.center, angle);

    newRange.min = Math::min(A.dotProduct(dir), B.dotProduct(dir));
    newRange.max = Math::max(A.dotProduct(dir), B.dotProduct(dir));

    return newRange;
}

MyRange MyRange::rangeConvex(MyConvexPolygon poly, MyVector2 dir)
{
    MyRange newRange;
    newRange.min = 0.f;
    newRange.max = 0.f;

    newRange.rangeInit(Math::min(poly.points[0].dotProduct(dir), poly.points[1].dotProduct(dir)));

    for (int i = 0; i < poly.count; ++i)
    {
        MyVector2 A, B;
        A = poly.points[i];
        B = poly.points[(i + 1) % poly.count];

        newRange.rangeAddValue(Math::min(A.dotProduct(dir), B.dotProduct(dir)));
        newRange.rangeAddValue(Math::max(A.dotProduct(dir), B.dotProduct(dir)));
    }

    return newRange;
}