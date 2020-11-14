#pragma once

#include <iostream>

#include "raylib.h"

#include "math.hpp"

#include "world.hpp"
#include "player.hpp"

Player::Player()
{

}

Player::Player(World game)
{
    MyVector2* points = new MyVector2[3];
    points[0].x = game.center.x;
    points[0].y = game.center.y + 20;
    points[1].x = game.center.x + 15;
    points[1].y = game.center.y - 10;
    points[2].x = game.center.x;
    points[2].y = game.center.y;
    MyVector2* points2 = new MyVector2[3];
    points[0].x = game.center.x;
    points[0].y = game.center.y + 20;
    points[1].x = game.center.x;
    points[1].y = game.center.y;
    points[2].x = game.center.x - 15;
    points[2].y = game.center.y - 10;

    direction = { 0.f, -1.f };
    thrust = 0.f;

    shape = points;
    shape = points2;

    for (auto& polygons : shape.polygons)
    {
        polygons.count = 3;
        polygons.angle = 0;
        polygons.center = game.center;

        local.angle = polygons.angle;
        local.origin = game.center;
        local.ui = {1.f, 0.f};
        local.uj = {0.f, -1.f};
    }
}

Player::~Player()
{
    for (auto& polygons : shape.polygons)
    {
        delete[] polygons.points;
    }
}

void Player::move()
{
    shape.polygons[0].center.x += thrust * direction.x;
    shape.polygons[0].center.y += thrust * direction.y;

    shape.polygons[0].center = local.posGlobalLocal(shape.polygons[0].center);

    for (int i = 0; i < shape.polygons[0].count; ++i)
    {
        shape.polygons[0].points[i] = local.posGlobalLocal(shape.polygons[0].points[i]);
    }
    
    shape.polygons[0].points[0].x = shape.polygons[0].center.x;
    shape.polygons[0].points[0].y = shape.polygons[0].center.y + 20;
    shape.polygons[0].points[1].x = shape.polygons[0].center.x + 15;
    shape.polygons[0].points[1].y = shape.polygons[0].center.y - 10;
    shape.polygons[0].points[2].x = shape.polygons[0].center.x;
    shape.polygons[0].points[2].y = shape.polygons[0].center.y;
    
    for (int i = 0; i < shape.polygons[0].count; ++i)
    {
        shape.polygons[0].points[i] = local.posLocalGlobal(shape.polygons[0].points[i]);
    }

    shape.polygons[0].center = local.posLocalGlobal(shape.polygons[0].center);



    shape.polygons[1].center.x += thrust * direction.x;
    shape.polygons[1].center.y += thrust * direction.y;

    shape.polygons[1].center = local.posGlobalLocal(shape.polygons[1].center);

    for (int i = 0; i < shape.polygons[1].count; ++i)
    {
        shape.polygons[1].points[i] = local.posGlobalLocal(shape.polygons[1].points[i]);
    }

    shape.polygons[1].points[0].x = shape.polygons[1].center.x;
    shape.polygons[1].points[0].y = shape.polygons[1].center.y + 20;
    shape.polygons[1].points[1].x = shape.polygons[1].center.x;
    shape.polygons[1].points[1].y = shape.polygons[1].center.y;
    shape.polygons[1].points[2].x = shape.polygons[1].center.x - 15;
    shape.polygons[1].points[2].y = shape.polygons[1].center.y - 10;

    for (int i = 0; i < shape.polygons[1].count; ++i)
    {
        shape.polygons[1].points[i] = local.posLocalGlobal(shape.polygons[1].points[i]);
    }

    shape.polygons[1].center = local.posLocalGlobal(shape.polygons[1].center);
}

void Player::update()
{
    float rotation = ((double)IsKeyDown(KEY_G) - (double)IsKeyDown(KEY_D)) * 4 * M_PI / 180;

    for (auto& polygons : shape.polygons)
    {
        local.angle = polygons.angle;
        local.rotateReferential(rotation);
        local.origin = polygons.center;

        //TODO: drift

        //DrawLine(polygons.center.x, polygons.center.y, (local.ui * 100 + polygons.center).x, (local.ui * 100 + polygons.center).y, RED);
        //DrawLine(polygons.center.x, polygons.center.y, (local.uj * 100 + polygons.center).x, (local.uj * 100 + polygons.center).y, BLUE);
        //DrawLine(polygons.center.x, polygons.center.y, (direction * 100 + polygons.center).x, (direction * 100 + polygons.center).y, YELLOW);

        direction = direction.vectorRotation(rotation);
    }
}