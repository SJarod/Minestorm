#include "collisiondetection.hpp"

#include "math.hpp"

#include "myvector2.hpp"
//#include "myrange.hpp"

#include <cmath>

bool Collide::PointBox(MyVector2 p1, MyRectangle box)
{
    return p1.x >= box.center.x - box.width / 2 && p1.x <= box.center.x + box.width / 2 &&
        p1.y >= box.center.y - box.height / 2 && p1.y <= box.center.y + box.height / 2;
}

bool Collide::BoxBox(MyRectangle& b1, MyRectangle& b2)
{
    MyVector2 nearestPt;
    nearestPt.x = Math::clamp(b2.center.x, b1.center.x - b1.width / 2, b1.center.x + b1.width / 2);
    nearestPt.y = Math::clamp(b2.center.y, b1.center.y - b1.height / 2, b1.center.y + b1.height / 2);

    if (PointBox(b2.center, b1))
    {
        return true;
    }
    else if (PointBox(nearestPt, b2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Collide::CircleBox(MyCircle& c1, MyRectangle& box)
{
    MyVector2 nearestPt;
    nearestPt.x = Math::clamp(c1.center.x, box.center.x - box.width / 2, box.center.x + box.width / 2);
    nearestPt.y = Math::clamp(c1.center.y, box.center.y - box.height / 2, box.center.y + box.height / 2);

    float m_mag = nearestPt.pointsDistance(c1.center);

    if (PointBox(c1.center, box))
    {
        return true;
    }
    else if (m_mag * m_mag <= c1.radius * c1.radius)
    {
        return true;
    }

    return false;
}

bool Collide::PointPoint(MyVector2 p1, MyVector2 p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) <= FLT_EPSILON;
}

bool Collide::PointCircle(MyVector2 p1, MyCircle c1)
{
    float mag = c1.center.pointsVector(p1).vectorMagnitude();
    return mag * mag <= c1.radius * c1.radius;
}

bool Collide::CircleCircle(MyCircle c1, MyCircle c2)
{
    float angle = MyVector2{ 1, c1.center.y }.pointsVector(c1.center).vectorAngle(c1.center.pointsVector(c2.center));

    MyVector2 nearestPt;
    nearestPt.x = Math::clamp(c2.center.x,
        c1.center.x - c1.radius * cosf(angle),
        c1.center.x + c1.radius * cosf(angle));
    nearestPt.y = Math::clamp(c2.center.y,
        c1.center.y - c1.radius * sinf(angle),
        c1.center.y + c1.radius * sinf(angle));

    float mag = nearestPt.pointsDistance(c2.center);

    if (PointCircle(c1.center, c2))
    {
        return true;
    }
    else if (mag * mag <= c2.radius * c2.radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}