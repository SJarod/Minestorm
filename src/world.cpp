#include "world.hpp"

#include "player.hpp"
#include "bullet.hpp"

World::World()
{

}

World::World(int screenWidth, int screenHeight)
{
    m_gameSpeed = 1.f;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

	m_center.x = (float)screenWidth / 2;
	m_center.y = (float)screenHeight / 2;
}

int World::getScreenWidth()
{
    return screenWidth;
}

int World::getScreenHeight()
{
    return screenHeight;
}

void World::playerOnEdge(Player& player)
{
    for (auto& polygons : player.m_shape.polygons)
    {
        if (polygons.center.x < 40)
        {
            polygons.center.x = screenWidth - 40;
        }
        if (polygons.center.x > screenWidth - 40)
        {
            polygons.center.x = 40;
        }
        if (polygons.center.y < 40)
        {
            polygons.center.y = screenHeight - 60;
        }
        if (polygons.center.y > screenHeight - 60)
        {
            polygons.center.y = 40;
        }
    }
}

void World::bulletOnEdge(Bullet& bullet)
{
    if (bullet.m_shape.center.x < 40)
    {
        bullet.m_shape.center.x = screenWidth - 40;
    }
    if (bullet.m_shape.center.x > screenWidth - 40)
    {
        bullet.m_shape.center.x = 40;
    }
    if (bullet.m_shape.center.y < 40)
    {
        bullet.m_shape.center.y = screenHeight - 60;
    }
    if (bullet.m_shape.center.y > screenHeight - 60)
    {
        bullet.m_shape.center.y = 40;
    }
}

void World::enemyOnEdge(Enemy& enemy)
{
    for (auto& polygons : enemy.m_shape.polygons)
    {
        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] -= polygons.center;
        }

        if (polygons.center.x < 40)
        {
            polygons.center.x = screenWidth - 40;
        }
        if (polygons.center.x > screenWidth - 40)
        {
            polygons.center.x = 40;
        }
        if (polygons.center.y < 40)
        {
            polygons.center.y = screenHeight - 60;
        }
        if (polygons.center.y > screenHeight - 60)
        {
            polygons.center.y = 40;
        }

        for (int i = 0; i < polygons.count; ++i)
        {
            polygons.points[i] += polygons.center;
        }
    }
}