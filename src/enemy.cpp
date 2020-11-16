#include "math.hpp"

#include "enemy.hpp"

Enemy::Enemy()
{

}

Enemy::Enemy(World game)
{
    
}

Enemy::~Enemy()
{
    delete[] m_shape.points;

    for (auto& polygons : m_shape.polygons)
    {
        delete[] polygons.points;
    }
}

FloatingMine::FloatingMine()
{
}

FloatingMine::FloatingMine(World game)
{
    MyVector2* points = new MyVector2[7];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 10;
    points[1].y = 0 - 5;
    points[2].x = 0;
    points[2].y = 0 - 35;
    points[3] = points[1].vectorRotation(2 * M_PI / 3);
    points[4] = points[2].vectorRotation(2 * M_PI / 3);
    points[5] = points[3].vectorRotation(2 * M_PI / 3);
    points[6] = points[4].vectorRotation(2 * M_PI / 3);

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape.points = points;

    MyVector2* pt = new MyVector2[4];
    pt[0] = points[1];
    pt[1] = points[2];
    pt[2] = points[3];
    pt[3] = points[0];
    MyConvexPolygon temp = pt;
    m_shape = temp;
    MyVector2* pt2 = new MyVector2[4];
    pt2[0] = points[3];
    pt2[1] = points[4];
    pt2[2] = points[5];
    pt2[3] = points[0];
    MyConvexPolygon temp2 = pt2;
    m_shape = temp2;
    MyVector2* pt3 = new MyVector2[4];
    pt3[0] = points[5];
    pt3[1] = points[6];
    pt3[2] = points[1];
    pt3[3] = points[0];
    MyConvexPolygon temp3 = pt3;
    m_shape = temp3;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] += game.center;
        polygons.points[1] += game.center;
        polygons.points[2] += game.center;
        polygons.points[3] += game.center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 4;
        polygons.angle = 0;
        polygons.center = game.center;

        m_local.angle = polygons.angle;
        m_local.origin = game.center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

FireballMine::FireballMine()
{

}

FireballMine::FireballMine(World game)
{
    MyVector2* points = new MyVector2[9];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 10;
    points[1].y = 0 - 5;
    points[2].x = 0;
    points[2].y = 0 - 35;
    points[3] = points[1].vectorRotation(M_PI / 2);
    points[4] = points[2].vectorRotation(M_PI / 2);
    points[5] = points[3].vectorRotation(M_PI / 2);
    points[6] = points[4].vectorRotation(M_PI / 2);
    points[7] = points[5].vectorRotation(M_PI / 2);
    points[8] = points[6].vectorRotation(M_PI / 2);

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape.points = points;

    MyVector2* pt = new MyVector2[4];
    pt[0] = points[1];
    pt[1] = points[2];
    pt[2] = points[3];
    pt[3] = points[0];
    MyConvexPolygon temp = pt;
    m_shape = temp;
    MyVector2* pt2 = new MyVector2[4];
    pt2[0] = points[3];
    pt2[1] = points[4];
    pt2[2] = points[5];
    pt2[3] = points[0];
    MyConvexPolygon temp2 = pt2;
    m_shape = temp2;
    MyVector2* pt3 = new MyVector2[4];
    pt3[0] = points[5];
    pt3[1] = points[6];
    pt3[2] = points[7];
    pt3[3] = points[0];
    MyConvexPolygon temp3 = pt3;
    m_shape = temp3;
    MyVector2* pt4 = new MyVector2[4];
    pt4[0] = points[7];
    pt4[1] = points[8];
    pt4[2] = points[1];
    pt4[3] = points[0];
    MyConvexPolygon temp4 = pt4;
    m_shape = temp4;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] += game.center;
        polygons.points[1] += game.center;
        polygons.points[2] += game.center;
        polygons.points[3] += game.center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 4;
        polygons.angle = 0;
        polygons.center = game.center;

        m_local.angle = polygons.angle;
        m_local.origin = game.center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

MagneticMine::MagneticMine()
{

}

MagneticMine::MagneticMine(World game)
{
    MyVector2* points = new MyVector2[9];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 10;
    points[1].y = 0 - 5;
    points[2].x = 0;
    points[2].y = 0 - 35;
    points[3] = points[1].vectorRotation(M_PI / 2);
    points[4] = points[2].vectorRotation(M_PI / 2);
    points[5] = points[3].vectorRotation(M_PI / 2);
    points[6] = points[4].vectorRotation(M_PI / 2);
    points[7] = points[5].vectorRotation(M_PI / 2);
    points[8] = points[6].vectorRotation(M_PI / 2);

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape.points = points;

    MyVector2* pt = new MyVector2[4];
    pt[0] = points[1];
    pt[1] = points[2];
    pt[2] = points[3];
    pt[3] = points[0];
    MyConvexPolygon temp = pt;
    m_shape = temp;
    MyVector2* pt2 = new MyVector2[4];
    pt2[0] = points[3];
    pt2[1] = points[4];
    pt2[2] = points[5];
    pt2[3] = points[0];
    MyConvexPolygon temp2 = pt2;
    m_shape = temp2;
    MyVector2* pt3 = new MyVector2[4];
    pt3[0] = points[5];
    pt3[1] = points[6];
    pt3[2] = points[7];
    pt3[3] = points[0];
    MyConvexPolygon temp3 = pt3;
    m_shape = temp3;
    MyVector2* pt4 = new MyVector2[4];
    pt4[0] = points[7];
    pt4[1] = points[8];
    pt4[2] = points[1];
    pt4[3] = points[0];
    MyConvexPolygon temp4 = pt4;
    m_shape = temp4;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] += game.center;
        polygons.points[1] += game.center;
        polygons.points[2] += game.center;
        polygons.points[3] += game.center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 4;
        polygons.angle = 0;
        polygons.center = game.center;

        m_local.angle = polygons.angle;
        m_local.origin = game.center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

MagneticFireballMine::MagneticFireballMine()
{

}

MagneticFireballMine::MagneticFireballMine(World game)
{
    MyVector2* points = new MyVector2[9];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 20;
    points[1].y = 0 + 10;
    points[2].x = 0 - 20;
    points[2].y = 0 - 35;
    points[3] = points[1].vectorRotation(M_PI / 2);
    points[4] = points[2].vectorRotation(M_PI / 2);
    points[5] = points[3].vectorRotation(M_PI / 2);
    points[6] = points[4].vectorRotation(M_PI / 2);
    points[7] = points[5].vectorRotation(M_PI / 2);
    points[8] = points[6].vectorRotation(M_PI / 2);

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape.points = points;

    MyVector2* pt = new MyVector2[3];
    pt[0] = points[1];
    pt[1] = points[2];
    pt[2] = points[3];
    MyConvexPolygon temp = pt;
    m_shape = temp;
    MyVector2* pt2 = new MyVector2[3];
    pt2[0] = points[3];
    pt2[1] = points[4];
    pt2[2] = points[5];
    MyConvexPolygon temp2 = pt2;
    m_shape = temp2;
    MyVector2* pt3 = new MyVector2[3];
    pt3[0] = points[5];
    pt3[1] = points[6];
    pt3[2] = points[7];
    MyConvexPolygon temp3 = pt3;
    m_shape = temp3;
    MyVector2* pt4 = new MyVector2[3];
    pt4[0] = points[7];
    pt4[1] = points[8];
    pt4[2] = points[1];
    MyConvexPolygon temp4 = pt4;
    m_shape = temp4;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] += game.center;
        polygons.points[1] += game.center;
        polygons.points[2] += game.center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 3;
        polygons.angle = 0;
        polygons.center = game.center;

        m_local.angle = polygons.angle;
        m_local.origin = game.center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

Fireball::Fireball()
{

}

Fireball::Fireball(World game)
{
    MyVector2* points = new MyVector2[3];
    points[0].x = 0 - 10;
    points[0].y = 0 - 5;
    points[1].x = 0;
    points[1].y = 0 - 35;
    points[2].x = 0 + 10;
    points[2].y = 0 - 5;
    MyVector2* points2 = new MyVector2[3];
    points2[0].x = 0 - 10;
    points2[0].y = 0 - 5;
    points2[1].x = 0;
    points2[1].y = 0 - 35;
    points2[2].x = 0 + 10;
    points2[2].y = 0 - 5;
    MyVector2* points3 = new MyVector2[3];
    points3[0].x = 0 - 10;
    points3[0].y = 0 - 5;
    points3[1].x = 0;
    points3[1].y = 0 - 35;
    points3[2].x = 0 + 10;
    points3[2].y = 0 - 5;

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape = points;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(2 * M_PI / 3);
        polygons.points[1] = polygons.points[1].vectorRotation(2 * M_PI / 3);
        polygons.points[2] = polygons.points[2].vectorRotation(2 * M_PI / 3);
    }
    m_shape = points2;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(2 * M_PI / 3);
        polygons.points[1] = polygons.points[1].vectorRotation(2 * M_PI / 3);
        polygons.points[2] = polygons.points[2].vectorRotation(2 * M_PI / 3);
    }
    m_shape = points3;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] += game.center;
        polygons.points[1] += game.center;
        polygons.points[2] += game.center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 3;
        polygons.angle = 0;
        polygons.center = game.center;

        m_local.angle = polygons.angle;
        m_local.origin = game.center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

Minelayer::Minelayer()
{

}

Minelayer::Minelayer(World game)
{
    MyVector2* points = new MyVector2[10];
    points[0].x = game.center.x;
    points[0].y = game.center.y;
    points[1].x = game.center.x - 100;
    points[1].y = game.center.y - 10;
    points[2].x = game.center.x - 10;
    points[2].y = game.center.y - 10;
    points[3].x = game.center.x;
    points[3].y = game.center.y - 30;
    points[4].x = game.center.x + 10;
    points[4].y = game.center.y - 10;
    points[5].x = game.center.x + 100;
    points[5].y = game.center.y - 10;
    points[6].x = game.center.x + 110;
    points[6].y = game.center.y + 25;
    points[7].x = game.center.x + 90;
    points[7].y = game.center.y + 10;
    points[8].x = game.center.x - 90;
    points[8].y = game.center.y + 10;
    points[9].x = game.center.x - 110;
    points[9].y = game.center.y + 25;

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape.points = points;

    MyVector2* pt = new MyVector2[3];
    pt[0] = points[1];
    pt[1] = points[8];
    pt[2] = points[9];
    MyConvexPolygon temp = pt;
    m_shape = temp;
    MyVector2* pt2 = new MyVector2[4];
    pt2[0] = points[1];
    pt2[1] = points[5];
    pt2[2] = points[7];
    pt2[3] = points[8];
    MyConvexPolygon temp2 = pt2;
    m_shape = temp2;
    MyVector2* pt3 = new MyVector2[3];
    pt3[0] = points[2];
    pt3[1] = points[3];
    pt3[2] = points[4];
    MyConvexPolygon temp3 = pt3;
    m_shape = temp3;
    MyVector2* pt4 = new MyVector2[3];
    pt4[0] = points[5];
    pt4[1] = points[6];
    pt4[2] = points[7];
    MyConvexPolygon temp4 = pt4;
    m_shape = temp4;

    m_shape.polygons[0].count = 3;
    m_shape.polygons[1].count = 4;
    m_shape.polygons[2].count = 3;
    m_shape.polygons[3].count = 3;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.angle = 0;
        polygons.center = game.center;

        m_local.angle = polygons.angle;
        m_local.origin = game.center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}