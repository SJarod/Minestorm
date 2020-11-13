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
    MyVector2* points = new MyVector2[4];
    points[0].x = game.center.x;
    points[0].y = game.center.y + 20;
    points[1].x = game.center.x + 15;
    points[1].y = game.center.y - 10;
    points[2].x = game.center.x;
    points[2].y = game.center.y;
    points[3].x = game.center.x - 15;
    points[3].y = game.center.y - 10;

    direction = { 0.f, -1.f };
    thrust = 0.f;

    shape = points;
    shape.count = 4;
    shape.angle = 0;
    shape.center = game.center;

    local.angle = shape.angle;
    local.origin = game.center;
    local.ui = {1.f, 0.f};
    local.uj = {0.f, -1.f};
}

Player::~Player()
{
    delete[] shape.points;
}

void Player::move()
{
    shape.center.x += thrust * direction.x;
    shape.center.y += thrust * direction.y;

    shape.center = local.posGlobalLocal(shape.center);

    for (int i = 0; i < shape.count; ++i)
    {
        shape.points[i] = local.posGlobalLocal(shape.points[i]);
    }
    
    shape.points[0].x = shape.center.x;
    shape.points[0].y = shape.center.y + 20;
    shape.points[1].x = shape.center.x + 15;
    shape.points[1].y = shape.center.y - 10;
    shape.points[2].x = shape.center.x;
    shape.points[2].y = shape.center.y;
    shape.points[3].x = shape.center.x - 15;
    shape.points[3].y = shape.center.y - 10;
    
    for (int i = 0; i < shape.count; ++i)
    {
        shape.points[i] = local.posLocalGlobal(shape.points[i]);
    }

    shape.center = local.posLocalGlobal(shape.center);
}

void Player::update()
{
    float rotation = ((double)IsKeyDown(KEY_G) - (double)IsKeyDown(KEY_D)) * 4 * M_PI / 180;

    local.angle = shape.angle;
    local.rotateReferential(rotation);
    local.origin = shape.center;

    //TODO: drift

    DrawLine(shape.center.x, shape.center.y, (local.ui * 100 + shape.center).x, (local.ui * 100 + shape.center).y, RED);
    DrawLine(shape.center.x, shape.center.y, (local.uj * 100 + shape.center).x, (local.uj * 100 + shape.center).y, BLUE);
    DrawLine(shape.center.x, shape.center.y, (direction * 100 + shape.center).x, (direction * 100 + shape.center).y, YELLOW);

    direction = direction.vectorRotation(rotation);
}

void Player::draw() const
{
    for (int i = 0; i < shape.count; ++i)
    {
        DrawLine(shape.points[i].x, shape.points[i].y, shape.points[(i + 1) % shape.count].x, shape.points[(i + 1) % shape.count].y, GREEN);
    }
}