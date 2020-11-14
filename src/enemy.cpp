#include "math.hpp"

#include "enemy.hpp"

Enemy::Enemy()
{

}

Enemy::Enemy(World game)
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

    direction = { 0.f, -1.f };
    thrust = 0.f;

    shape = points;
    for (auto& polygons : shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(2 * M_PI / 3);
        polygons.points[1] = polygons.points[1].vectorRotation(2 * M_PI / 3);
        polygons.points[2] = polygons.points[2].vectorRotation(2 * M_PI / 3);
    }
    shape = points2;
    for (auto& polygons : shape.polygons)
    {
        polygons.points[0] = polygons.points[0].vectorRotation(2 * M_PI / 3);
        polygons.points[1] = polygons.points[1].vectorRotation(2 * M_PI / 3);
        polygons.points[2] = polygons.points[2].vectorRotation(2 * M_PI / 3);
    }
    shape = points3;

    for (auto& polygons : shape.polygons)
    {
        polygons.points[0] += game.center;
        polygons.points[1] += game.center;
        polygons.points[2] += game.center;
    }

    for (auto& polygons : shape.polygons)
    {
        polygons.count = 3;
        polygons.angle = 0;
        polygons.center = game.center;

        local.angle = polygons.angle;
        local.origin = game.center;
        local.ui = { 1.f, 0.f };
        local.uj = { 0.f, -1.f };
    }
}

Enemy::~Enemy()
{

}