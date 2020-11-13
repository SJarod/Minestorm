#pragma once

#include "myvector2.hpp"

class World
{
private:
	int level = 1;

public:
	MyVector2 center;

	World();
	World(int screenWidth, int screenHeight);
};