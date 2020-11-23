#include "raylib.h"

#include "entity.hpp"
#include "world.hpp"

void Entity::draw(Color color) const
{
    for (auto& polygons : m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            DrawLine(polygons.points[i].x, polygons.points[i].y, polygons.points[(i + 1) % polygons.count].x, polygons.points[(i + 1) % polygons.count].y, color);
        }
    }
}

void Entity::draw(MyVector2 pos, Color color) const
{
    for (auto& polygons : m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] -= polygons.center;
        }

        for (int i = 0; i < polygons.count; ++i)
        {
            DrawLine(polygons.points[i].x + pos.x,
                     polygons.points[i].y + pos.y,
                     polygons.points[(i + 1) % polygons.count].x + pos.x,
                     polygons.points[(i + 1) % polygons.count].y + pos.y,
                     color);
        }

        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] += polygons.center;
        }
    }
}

void Entity::teleport(MyVector2 pos)
{
    for (auto& polygons : m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] -= polygons.center;
        }

        polygons.center = pos;

        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] += polygons.center;
        }
    }
}

void Entity::teleport(World& game)
{
    MyVector2 newPos;
    newPos.x = rand() % game.getScreenWidth(-200) + 100;
    newPos.y = rand() % game.getScreenHeight(-200) + 100;

    for (auto& polygons : m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] -= polygons.center;
        }

        polygons.center = newPos;

        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] += polygons.center;
        }
    }
}