#pragma once

#include <iostream>

#include "raylib.h"

#include "math.hpp"

#include "world.hpp"
#include "player.hpp"

Player::Player()
{

}

Player::Player(World& game)
{
    MyVector2* points = new MyVector2[4];
    points[0].x = 0;
    points[0].y = 0;
    points[1].x = 0 - 15;
    points[1].y = 0 - 10;
    points[2].x = 0;
    points[2].y = 0 + 20;
    points[3].x = 0 + 15;
    points[3].y = 0 - 10;

    m_direction = { 0.f, -1.f };
    m_speed = { 0.f, -1.f };
    m_thrust = 0.f;

    m_shape.points = points;

    MyVector2* pt = new MyVector2[3];
    pt[0] = points[1];
    pt[1] = points[2];
    pt[2] = points[0];
    MyConvexPolygon temp = pt;
    m_shape = temp;
    MyVector2* pt2 = new MyVector2[3];
    pt2[0] = points[2];
    pt2[1] = points[3];
    pt2[2] = points[0];
    MyConvexPolygon temp2 = pt2;
    m_shape = temp2;

    m_direction = { 0.f, -1.f };
    m_thrust = 0.f;

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
        m_local.ui = {1.f, 0.f};
        m_local.uj = {0.f, -1.f};
    }
}

Player::~Player()
{
    //delete[] m_shape.points;

    //for (auto& polygons : m_shape.polygons)
    //{
    //    delete[] polygons.points;
    //}
}

void Player::shoot(float currentTime)
{
    Bullet bullet(m_shape.polygons[0].center, m_local.uj, currentTime);

    m_bullet.push_back(bullet);
}

//TODO : look at Enemy::move()
void Player::move(World& game, float deltaTime, float gameSpeed)
{
    if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_T))
    {
        teleport(game);
    }



    //for (auto& polygons : m_shape.polygons)
    //{
    //    polygons.center = m_local.posGlobalLocal(polygons.center);

    //    for (int i = 0; i < polygons.count; ++i)
    //    {
    //        polygons.points[i] = m_local.posGlobalLocal(polygons.points[i]);
    //        polygons.points[i] -= polygons.center;
    //    }

    //    polygons.center += m_speed * m_thrust * deltaTime * gameSpeed;

    //    for (int i = 0; i < polygons.count; ++i)
    //    {
    //        polygons.points[i] += polygons.center;
    //        polygons.points[i] = m_local.posLocalGlobal(polygons.points[i]);
    //    }

    //    polygons.center = m_local.posLocalGlobal(polygons.center);
    //}



    m_shape.polygons[0].center += m_speed * m_thrust * deltaTime * gameSpeed;

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



    m_shape.polygons[1].center += m_speed * m_thrust * deltaTime * gameSpeed;

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

void Player::update(float deltaTime, float gameSpeed)
{
    float rotation = ((double)IsKeyDown(KEY_G) - (double)IsKeyDown(KEY_D)) * 4 * M_PI / 180 * deltaTime * gameSpeed;

    for (auto& polygons : m_shape.polygons)
    {
        m_local.angle = polygons.angle;
        m_local.rotateReferential(rotation);
        m_local.origin = polygons.center;

        //DrawLine(polygons.center.x, polygons.center.y, (m_local.ui * 100 + polygons.center).x, (m_local.ui * 100 + polygons.center).y, RED);
        //DrawLine(polygons.center.x, polygons.center.y, (m_local.uj * 100 + polygons.center).x, (m_local.uj * 100 + polygons.center).y, BLUE);
        //DrawLine(polygons.center.x, polygons.center.y, (m_direction * 100 + polygons.center).x, (m_direction * 100 + polygons.center).y, YELLOW);
        //DrawLine(polygons.center.x, polygons.center.y, (m_speed * 100 + polygons.center).x, (m_speed * 100 + polygons.center).y, GREEN);

        m_direction = m_direction.vectorRotation(rotation);

        float angle = m_speed.vectorAngle(m_direction);

        if (fabsf(angle) >= M_PI / 2)
        {
            m_speed = m_speed.vectorRotation(rotation);
        }

        if (angle != 0)
        {
            m_speed = m_speed.vectorRotation(2 * M_PI / 180 * angle / fabsf(angle));
        }
    }
}