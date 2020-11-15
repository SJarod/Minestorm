#include "collisiondetection.hpp"

#include "math.hpp"

#include "myvector2.hpp"
#include "myrange.hpp"

#include <cmath>

#include <iostream>

bool Collide::cPointBox(MyVector2 p1, MyRectangle box)
{
    return p1.x >= box.center.x - box.width / 2 && p1.x <= box.center.x + box.width / 2 &&
        p1.y >= box.center.y - box.height / 2 && p1.y <= box.center.y + box.height / 2;
}

bool Collide::cBoxBox(MyRectangle& b1, MyRectangle& b2)
{
    MyVector2 nearestPt;
    nearestPt.x = Math::clamp(b2.center.x, b1.center.x - b1.width / 2, b1.center.x + b1.width / 2);
    nearestPt.y = Math::clamp(b2.center.y, b1.center.y - b1.height / 2, b1.center.y + b1.height / 2);

    if (cPointBox(b2.center, b1))
    {
        return true;
    }
    else if (cPointBox(nearestPt, b2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Collide::cCircleBox(MyCircle& c1, MyRectangle& box)
{
    MyVector2 nearestPt;
    nearestPt.x = Math::clamp(c1.center.x, box.center.x - box.width / 2, box.center.x + box.width / 2);
    nearestPt.y = Math::clamp(c1.center.y, box.center.y - box.height / 2, box.center.y + box.height / 2);

    float m_mag = nearestPt.pointsDistance(c1.center);

    if (cPointBox(c1.center, box))
    {
        return true;
    }
    else if (m_mag * m_mag <= c1.radius * c1.radius)
    {
        return true;
    }

    return false;
}

bool Collide::cPointPoint(MyVector2 p1, MyVector2 p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) <= FLT_EPSILON;
}

bool Collide::cPointCircle(MyVector2 p1, MyCircle c1)
{
    float mag = c1.center.pointsVector(p1).vectorMagnitude();
    return mag * mag <= c1.radius * c1.radius;
}

bool Collide::cCircleCircle(MyCircle c1, MyCircle c2)
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

    if (cPointCircle(c1.center, c2))
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

bool	Collide::cConvexBox(MyConvexPolygon p1, MyRectangle box)
{
    return false;
}

bool	Collide::cConvexCircle(MyConvexPolygon p1, MyCircle c1)
{
    std::vector<MyRange> range;
    std::vector<MyVector2> normal;

    for (int i = 0; i < p1.count; ++i)
    {
        MyVector2 temp = (p1.points[i].pointsVector(p1.points[(i + 1) % p1.count])).normalVector();
        normal.push_back(temp);
    }

    for (int i = 0; i < p1.count; ++i)
    {
        MyRange temp;
        temp = temp.rangeConvex(p1, normal[i]);
        range.push_back(temp);
    }

    std::vector<MyRange> range2;

    for (int i = 0; i < p1.count; ++i)
    {
        MyRange temp;
        temp = temp.rangeCircle(c1, normal[i]);
        range2.push_back(temp);
    }

    for (int i = 0; i < p1.count; ++i)
    {
        if (!range[i].rangeCollision(range2[i]))
        {
            return false;
        }
    }

    return true;
}

bool	Collide::cConvexConvex(MyConvexPolygon p1, MyConvexPolygon p2)
{
    //TODO : move "getting range" to a function
    std::vector<MyRange> range;
    std::vector<MyVector2> normal;

    for (int i = 0; i < p1.count; ++i)
    {
        MyVector2 temp = (p1.points[i].pointsVector(p1.points[(i + 1) % p1.count])).normalVector();
        normal.push_back(temp);
    }

    for (int i = 0; i < p1.count; ++i)
    {
        MyRange temp;
        temp = temp.rangeConvex(p1, normal[i]);
        range.push_back(temp);
    }

    std::vector<MyRange> range2;

    for (int i = 0; i < p1.count; ++i)
    {
        MyRange temp;
        temp = temp.rangeConvex(p2, normal[i]);
        range2.push_back(temp);
    }

    for (int i = 0; i < p1.count; ++i)
    {
        if (!range[i].rangeCollision(range2[i]))
        {
            return false;
        }
    }

    return true;
}

//TODO : cConcaveConcave()
bool	Collide::cPlayerEnemy(Player& player, Enemy& enemy)
{
    for (auto& playerPolygons : player.m_shape.polygons)
    {
        for (auto& enemyPolygons : enemy.m_shape.polygons)
        {
            for (int i = 0; i < playerPolygons.count; ++i)
                playerPolygons.points[i] = player.m_local.posGlobalLocal(playerPolygons.points[i]);

            for (int i = 0; i < enemyPolygons.count; ++i)
                enemyPolygons.points[i] = player.m_local.posGlobalLocal(enemyPolygons.points[i]);

            if (Collide::cConvexConvex(playerPolygons, enemyPolygons))
            {
                for (int i = 0; i < enemyPolygons.count; ++i)
                    enemyPolygons.points[i] = player.m_local.posLocalGlobal(enemyPolygons.points[i]);

                for (int i = 0; i < playerPolygons.count; ++i)
                    playerPolygons.points[i] = player.m_local.posLocalGlobal(playerPolygons.points[i]);

                return true;
            }
            else
            {
                for (int i = 0; i < enemyPolygons.count; ++i)
                    enemyPolygons.points[i] = player.m_local.posLocalGlobal(enemyPolygons.points[i]);

                for (int i = 0; i < playerPolygons.count; ++i)
                    playerPolygons.points[i] = player.m_local.posLocalGlobal(playerPolygons.points[i]);
            }
        }
    }

    return false;
}

bool	Collide::cBulletEnemy(Player& player, Enemy& enemy)
{
    for (auto& enemyPolygons : enemy.m_shape.polygons)
    {
        int index = 0;

        for (auto& bullet : player.m_bullet)
        {
            bullet.m_shape.center = enemy.m_local.posGlobalLocal(bullet.m_shape.center);

            for (int i = 0; i < enemyPolygons.count; ++i)
                enemyPolygons.points[i] = enemy.m_local.posGlobalLocal(enemyPolygons.points[i]);

            if (Collide::cConvexCircle(enemyPolygons, bullet.m_shape))
            {
                for (int i = 0; i < enemyPolygons.count; ++i)
                    enemyPolygons.points[i] = enemy.m_local.posLocalGlobal(enemyPolygons.points[i]);

                bullet.m_shape.center = enemy.m_local.posLocalGlobal(bullet.m_shape.center);

                player.m_bullet.erase(player.m_bullet.begin() + index);
                return true;
            }
            else
            {
                for (int i = 0; i < enemyPolygons.count; ++i)
                    enemyPolygons.points[i] = enemy.m_local.posLocalGlobal(enemyPolygons.points[i]);

                bullet.m_shape.center = enemy.m_local.posLocalGlobal(bullet.m_shape.center);
            }

            ++index;
        }
    }

    return false;
}