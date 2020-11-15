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

FireballMine::FireballMine()
{

}

FireballMine::FireballMine(World game)
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
    MyVector2* points4 = new MyVector2[3];
    points4[0].x = 0 - 10;
    points4[0].y = 0 - 5;
    points4[1].x = 0;
    points4[1].y = 0 - 35;
    points4[2].x = 0 + 10;
    points4[2].y = 0 - 5;

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape = points;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(M_PI / 2);
        polygons.points[1] = polygons.points[1].vectorRotation(M_PI / 2);
        polygons.points[2] = polygons.points[2].vectorRotation(M_PI / 2);
    }
    m_shape = points2;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(M_PI / 2);
        polygons.points[1] = polygons.points[1].vectorRotation(M_PI / 2);
        polygons.points[2] = polygons.points[2].vectorRotation(M_PI / 2);
    }
    m_shape = points3;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(M_PI / 2);
        polygons.points[1] = polygons.points[1].vectorRotation(M_PI / 2);
        polygons.points[2] = polygons.points[2].vectorRotation(M_PI / 2);
    }
    m_shape = points4;

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

MagneticMine::MagneticMine()
{

}

MagneticMine::MagneticMine(World game)
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
    MyVector2* points4 = new MyVector2[3];
    points4[0].x = 0 - 10;
    points4[0].y = 0 - 5;
    points4[1].x = 0;
    points4[1].y = 0 - 35;
    points4[2].x = 0 + 10;
    points4[2].y = 0 - 5;

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape = points;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(M_PI / 2);
        polygons.points[1] = polygons.points[1].vectorRotation(M_PI / 2);
        polygons.points[2] = polygons.points[2].vectorRotation(M_PI / 2);
    }
    m_shape = points2;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(M_PI / 2);
        polygons.points[1] = polygons.points[1].vectorRotation(M_PI / 2);
        polygons.points[2] = polygons.points[2].vectorRotation(M_PI / 2);
    }
    m_shape = points3;
    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(M_PI / 2);
        polygons.points[1] = polygons.points[1].vectorRotation(M_PI / 2);
        polygons.points[2] = polygons.points[2].vectorRotation(M_PI / 2);
    }
    m_shape = points4;

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

MagneticFireballMine::MagneticFireballMine()
{

}

MagneticFireballMine::MagneticFireballMine(World game)
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