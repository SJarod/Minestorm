#include "raylib.h"

#include "entity.hpp"

void Entity::draw() const
{
    for (auto& polygons : shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            DrawLine(polygons.points[i].x, polygons.points[i].y, polygons.points[(i + 1) % polygons.count].x, polygons.points[(i + 1) % polygons.count].y, GREEN);
        }
    }
}