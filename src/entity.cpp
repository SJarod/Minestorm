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

void Entity::teleport(World& game)
{
    MyVector2 newPos;
    newPos.x = rand() % game.getScreenWidth();
    newPos.y = rand() % game.getScreenHeight();

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