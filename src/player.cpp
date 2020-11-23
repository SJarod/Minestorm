#pragma once

#include <iostream>

#include "raylib.h"

#include "math.hpp"

#include "world.hpp"
#include "player.hpp"

Player::Player()
{

}

Player::Player(MyVector2 pos)
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

    m_pos = pos;

    for (auto& polygons : m_shape.polygons)
    {
        polygons.points[0] += pos;
        polygons.points[1] += pos;
        polygons.points[2] += pos;
    }

    for (auto& polygons : m_shape.polygons)
    {
        polygons.count = 3;
        polygons.angle = 0;
        polygons.center = pos;

        m_local.angle = polygons.angle;
        m_local.origin = pos;
        m_local.ui = {1.f, 0.f};
        m_local.uj = {0.f, -1.f};
    }
}

Player::~Player()
{
    delete[] m_shape.points;

    for (auto& polygons : m_shape.polygons)
    {
        delete[] polygons.points;
    }
}

int Player::getId() const
{
    return m_id;
}

int Player::getHealth() const
{
    return m_health;
}

void Player::addHealth()
{
    if (m_health < 3)
        ++m_health;
}

void Player::setSecondPlayer()
{
    m_id = 2;
    m_color = { 255, 128, 128, 255 };
}

void Player::setInputs()
{
    if (m_id == 1)
    {
        m_inputs.movingForward = IsKeyDown(KEY_R);
        m_inputs.rotateRight =   IsKeyDown(KEY_G);
        m_inputs.rotateLeft =    IsKeyDown(KEY_D);
        m_inputs.shooting =      IsKeyDown(KEY_F);
        m_inputs.teleporting =   IsKeyPressed(KEY_E) + IsKeyPressed(KEY_T);
    }
    else if (m_id == 2)
    {
        m_inputs.movingForward = IsKeyDown(KEY_I);
        m_inputs.rotateRight =   IsKeyDown(KEY_L);
        m_inputs.rotateLeft =    IsKeyDown(KEY_J);
        m_inputs.shooting =      IsKeyDown(KEY_K);
        m_inputs.teleporting =   IsKeyPressed(KEY_U) + IsKeyPressed(KEY_O);
    }
}

void Player::shoot(float currentTime)
{
    Bullet bullet(m_shape.polygons[0].center, m_local.uj, currentTime);

    m_bullet.push_back(bullet);
}

bool Player::isHit()
{
    --m_health;
    teleport(m_pos);

    if (m_health <= 0)
    {
        return true;
    }

    return false;
}

//TODO : look at Enemy::move()
void Player::move(World& game, float deltaTime)
{
    if (m_inputs.teleporting)
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

    //    polygons.center += m_speed * m_thrust * deltaTime * game.m_gameSpeed;

    //    for (int i = 0; i < polygons.count; ++i)
    //    {
    //        polygons.points[i] += polygons.center;
    //        polygons.points[i] = m_local.posLocalGlobal(polygons.points[i]);
    //    }

    //    polygons.center = m_local.posLocalGlobal(polygons.center);
    //}



    m_shape.polygons[0].center += m_speed * m_thrust * deltaTime * game.m_gameSpeed;

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



    m_shape.polygons[1].center += m_speed * m_thrust * deltaTime * game.m_gameSpeed;

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

void Player::update(float deltaTime, float m_gameSpeed)
{
    float rotation = (Math::toRadians((double)m_inputs.rotateRight - (double)m_inputs.rotateLeft) * 4 * deltaTime * m_gameSpeed);

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

        if (m_inputs.movingForward)
        {
            if (fabsf(angle) >= M_PI / 2)
            {
                m_speed = m_speed.vectorRotation(rotation);
            }
            if (angle != 0)
            {
                m_speed = m_speed.vectorRotation(Math::toRadians(2 * angle / fabsf(angle)));
            }
        }
        else if (m_thrust == 0)
        {
            m_speed = m_direction;
        }
    }
}