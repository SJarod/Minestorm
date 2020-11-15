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

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape = points;
    m_shape = points2;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 3;
        polygons.angle = 0;
        polygons.center = game.center;

        m_local.angle = polygons.angle;
        m_local.origin = game.center;
        m_local.ui = {1.f, 0.f};
        m_local.uj = {0.f, -1.f};
    }
}

Player::~Player()
{
    for (auto& polygons : m_shape.polygons)
    {
        delete[] polygons.points;
    }
}

void Player::shoot(float currentTime)
{
    Bullet bullet(m_shape.polygons[0].center, m_local.uj, currentTime);

    m_bullet.push_back(bullet);
}

void Player::move(World game, float deltaTime)
{
    if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_T))
    {
        teleport(game);
    }

    m_shape.polygons[0].center.x += m_thrust * m_direction.x * deltaTime;
    m_shape.polygons[0].center.y += m_thrust * m_direction.y * deltaTime;

    m_shape.polygons[0].center = m_local.posGlobalLocal(m_shape.polygons[0].center);

    for (int i = 0; i < m_shape.polygons[0].count; ++i)
    {
        m_shape.polygons[0].points[i] = m_local.posGlobalLocal(m_shape.polygons[0].points[i]);
    }
    
    m_shape.polygons[0].points[0].x = m_shape.polygons[0].center.x;
    m_shape.polygons[0].points[0].y = m_shape.polygons[0].center.y + 20;
    m_shape.polygons[0].points[1].x = m_shape.polygons[0].center.x + 15;
    m_shape.polygons[0].points[1].y = m_shape.polygons[0].center.y - 10;
    m_shape.polygons[0].points[2].x = m_shape.polygons[0].center.x;
    m_shape.polygons[0].points[2].y = m_shape.polygons[0].center.y;
    
    for (int i = 0; i < m_shape.polygons[0].count; ++i)
    {
        m_shape.polygons[0].points[i] = m_local.posLocalGlobal(m_shape.polygons[0].points[i]);
    }

    m_shape.polygons[0].center = m_local.posLocalGlobal(m_shape.polygons[0].center);



    m_shape.polygons[1].center.x += m_thrust * m_direction.x * deltaTime;
    m_shape.polygons[1].center.y += m_thrust * m_direction.y * deltaTime;

    m_shape.polygons[1].center = m_local.posGlobalLocal(m_shape.polygons[1].center);

    for (int i = 0; i < m_shape.polygons[1].count; ++i)
    {
        m_shape.polygons[1].points[i] = m_local.posGlobalLocal(m_shape.polygons[1].points[i]);
    }

    m_shape.polygons[1].points[0].x = m_shape.polygons[1].center.x;
    m_shape.polygons[1].points[0].y = m_shape.polygons[1].center.y + 20;
    m_shape.polygons[1].points[1].x = m_shape.polygons[1].center.x;
    m_shape.polygons[1].points[1].y = m_shape.polygons[1].center.y;
    m_shape.polygons[1].points[2].x = m_shape.polygons[1].center.x - 15;
    m_shape.polygons[1].points[2].y = m_shape.polygons[1].center.y - 10;

    for (int i = 0; i < m_shape.polygons[1].count; ++i)
    {
        m_shape.polygons[1].points[i] = m_local.posLocalGlobal(m_shape.polygons[1].points[i]);
    }

    m_shape.polygons[1].center = m_local.posLocalGlobal(m_shape.polygons[1].center);
}

void Player::teleport(World game)
{
    MyVector2 newPos;
    newPos.x = rand() % game.getScreenWidth();
    newPos.y = rand() % game.getScreenHeight();

    for (auto& polygons : m_shape.polygons)
    {
        polygons.center = newPos;
    }
}

void Player::update(float deltaTime)
{
    float rotation = ((double)IsKeyDown(KEY_G) - (double)IsKeyDown(KEY_D)) * 4 * M_PI / 180 * deltaTime;

    for (auto& polygons : m_shape.polygons)
    {
        m_local.angle = polygons.angle;
        m_local.rotateReferential(rotation);
        m_local.origin = polygons.center;

        //TODO: drift

        //DrawLine(polygons.center.x, polygons.center.y, (local.ui * 100 + polygons.center).x, (local.ui * 100 + polygons.center).y, RED);
        //DrawLine(polygons.center.x, polygons.center.y, (local.uj * 100 + polygons.center).x, (local.uj * 100 + polygons.center).y, BLUE);
        //DrawLine(polygons.center.x, polygons.center.y, (direction * 100 + polygons.center).x, (direction * 100 + polygons.center).y, YELLOW);

        m_direction = m_direction.vectorRotation(rotation);
    }
}