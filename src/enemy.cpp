#include "math.hpp"

#include "enemy.hpp"

#include "world.hpp"

Enemy::Enemy()
{

}

Enemy::Enemy(World& game)
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

void Enemy::move(World& game, float deltaTime)
{
    for (auto& polygons : m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] -= polygons.center;
        }

        polygons.center += m_speed * 1 * deltaTime * game.m_gameSpeed;

        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] += polygons.center;
        }
    }
}

bool Enemy::shoot()
{
    return false;
}

void Enemy::divide(World& game)
{
    if (game.m_spawnNum <= 0)
        return;

    if (m_size == BIG)
    {
        game.spawn(MEDIUM);
        game.spawn(MEDIUM);
    }
    else if (m_size == MEDIUM)
    {
        game.spawn(SMALL);
        game.spawn(SMALL);
    }
    else
        return;
}

FloatingMine::FloatingMine()
{

}

FloatingMine::FloatingMine(World& game, EnemySize size)
{
    m_size = size;

    float finalSize = size;
    if (finalSize == 0)
        finalSize = 0.5;

    MyVector2* points = new MyVector2[7];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 10 * finalSize;
    points[1].y = 0 - 5 * finalSize;
    points[2].x = 0;
    points[2].y = 0 - 35 * finalSize;
    points[3] = points[1].vectorRotation(2 * M_PI / 3);
    points[4] = points[2].vectorRotation(2 * M_PI / 3);
    points[5] = points[3].vectorRotation(2 * M_PI / 3);
    points[6] = points[4].vectorRotation(2 * M_PI / 3);

    m_direction = { 0.f, -1.f };
    m_speed = { Math::random(-1, 1), Math::random(-1, 1) };
    m_speed.normalizeVect();
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
        polygons.points[0] += game.m_center;
        polygons.points[1] += game.m_center;
        polygons.points[2] += game.m_center;
        polygons.points[3] += game.m_center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 4;
        polygons.angle = 0;
        polygons.center = game.m_center;

        m_local.angle = polygons.angle;
        m_local.origin = game.m_center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

FireballMine::FireballMine()
{

}

FireballMine::FireballMine(World& game, EnemySize size)
{
    m_size = size;

    float finalSize = size;
    if (finalSize == 0)
        finalSize = 0.5;

    MyVector2* points = new MyVector2[9];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 10 * finalSize;
    points[1].y = 0 - 15 * finalSize;
    points[2].x = 0;
    points[2].y = 0 - 35 * finalSize;
    points[3] = points[1].vectorRotation(M_PI / 2);
    points[4] = points[2].vectorRotation(M_PI / 2);
    points[5] = points[3].vectorRotation(M_PI / 2);
    points[6] = points[4].vectorRotation(M_PI / 2);
    points[7] = points[5].vectorRotation(M_PI / 2);
    points[8] = points[6].vectorRotation(M_PI / 2);

    m_direction = { 0.f, -1.f };
    m_speed = { Math::random(-1, 1), Math::random(-1, 1) };
    m_speed.normalizeVect();
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
        polygons.points[0] += game.m_center;
        polygons.points[1] += game.m_center;
        polygons.points[2] += game.m_center;
        polygons.points[3] += game.m_center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 4;
        polygons.angle = 0;
        polygons.center = game.m_center;

        m_local.angle = polygons.angle;
        m_local.origin = game.m_center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

bool FireballMine::shoot()
{
    return true;
}

MagneticMine::MagneticMine()
{

}

MagneticMine::MagneticMine(World& game, EnemySize size)
{
    m_size = size;

    float finalSize = size;
    if (finalSize == 0)
        finalSize = 0.5;

    MyVector2* points = new MyVector2[9];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 10 * finalSize;
    points[1].y = 0 - 5 * finalSize;
    points[2].x = 0;
    points[2].y = 0 - 35 * finalSize;
    points[3] = points[1].vectorRotation(M_PI / 2);
    points[4] = points[2].vectorRotation(M_PI / 2);
    points[5] = points[3].vectorRotation(M_PI / 2);
    points[6] = points[4].vectorRotation(M_PI / 2);
    points[7] = points[5].vectorRotation(M_PI / 2);
    points[8] = points[6].vectorRotation(M_PI / 2);

    m_direction = { 0.f, -1.f };
    m_speed = { Math::random(-1, 1), Math::random(-1, 1) };
    m_speed.normalizeVect();
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
        polygons.points[0] += game.m_center;
        polygons.points[1] += game.m_center;
        polygons.points[2] += game.m_center;
        polygons.points[3] += game.m_center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 4;
        polygons.angle = 0;
        polygons.center = game.m_center;

        m_local.angle = polygons.angle;
        m_local.origin = game.m_center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

void MagneticMine::move(World& game, float deltaTime)
{
    m_speed = m_shape.polygons[0].center.pointsVector(game.m_players[0]->m_shape.polygons[0].center).normalizeVect();

    for (auto& polygons : m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] -= polygons.center;
        }

        polygons.center -= m_speed * 1 * deltaTime * game.m_gameSpeed;

        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] += polygons.center;
        }
    }
}

MagneticFireballMine::MagneticFireballMine()
{

}

MagneticFireballMine::MagneticFireballMine(World& game, EnemySize size)
{
    m_size = size;

    float finalSize = size;
    if (finalSize == 0)
        finalSize = 0.5;

    MyVector2* points = new MyVector2[9];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 20 * finalSize;
    points[1].y = 0 + 10 * finalSize;
    points[2].x = 0 - 20 * finalSize;
    points[2].y = 0 - 35 * finalSize;
    points[3] = points[1].vectorRotation(M_PI / 2);
    points[4] = points[2].vectorRotation(M_PI / 2);
    points[5] = points[3].vectorRotation(M_PI / 2);
    points[6] = points[4].vectorRotation(M_PI / 2);
    points[7] = points[5].vectorRotation(M_PI / 2);
    points[8] = points[6].vectorRotation(M_PI / 2);

    m_direction = { 0.f, -1.f };
    m_speed = { Math::random(-1, 1), Math::random(-1, 1) };
    m_speed.normalizeVect();
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
        polygons.points[0] += game.m_center;
        polygons.points[1] += game.m_center;
        polygons.points[2] += game.m_center;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 3;
        polygons.angle = 0;
        polygons.center = game.m_center;

        m_local.angle = polygons.angle;
        m_local.origin = game.m_center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}

void MagneticFireballMine::move(World& game, float deltaTime)
{
    m_speed = m_shape.polygons[0].center.pointsVector(game.m_players[0]->m_shape.polygons[0].center).normalizeVect();

    for (auto& polygons : m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] -= polygons.center;
        }

        polygons.center -= m_speed * 1 * deltaTime * game.m_gameSpeed;

        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] += polygons.center;
        }
    }
}

bool MagneticFireballMine::shoot()
{
    return true;
}

Fireball::Fireball()
{

}

Fireball::Fireball(MyVector2 c, MyVector2 dir, float lifeTime)
{
    m_shape.center = c;
    m_shape.radius = 5.f;

    m_lifeTime = lifeTime;

    m_direction = dir;
}

void Fireball::move(float deltaTime, float gameSpeed)
{
    m_shape.center += m_direction * 10 * deltaTime * gameSpeed;
}

void Fireball::draw(Color color) const
{
    DrawCircle(m_shape.center.x, m_shape.center.y, m_shape.radius, color);
}

Minelayer::Minelayer()
{

}

Minelayer::Minelayer(World& game)
{
    MyVector2* points = new MyVector2[10];
    points[0].x = game.m_center.x;
    points[0].y = game.m_center.y;
    points[1].x = game.m_center.x - 100;
    points[1].y = game.m_center.y - 10;
    points[2].x = game.m_center.x - 10;
    points[2].y = game.m_center.y - 10;
    points[3].x = game.m_center.x;
    points[3].y = game.m_center.y - 30;
    points[4].x = game.m_center.x + 10;
    points[4].y = game.m_center.y - 10;
    points[5].x = game.m_center.x + 100;
    points[5].y = game.m_center.y - 10;
    points[6].x = game.m_center.x + 110;
    points[6].y = game.m_center.y + 25;
    points[7].x = game.m_center.x + 90;
    points[7].y = game.m_center.y + 10;
    points[8].x = game.m_center.x - 90;
    points[8].y = game.m_center.y + 10;
    points[9].x = game.m_center.x - 110;
    points[9].y = game.m_center.y + 25;

    m_direction = { 0.f, -1.f };
    m_speed = { Math::random(-1, 1), Math::random(-1, 1) };
    m_speed.normalizeVect();
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
        polygons.center = game.m_center;

        m_local.angle = polygons.angle;
        m_local.origin = game.m_center;
        m_local.ui = { 1.f, 0.f };
        m_local.uj = { 0.f, -1.f };
    }
}