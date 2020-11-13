#include "world.hpp"

World::World()
{

}

World::World(int screenWidth, int screenHeight)
{
	center.x = (float)screenWidth / 2;
	center.y = (float)screenHeight / 2;
}