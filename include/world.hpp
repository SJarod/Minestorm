#pragma once

#include "myvector2.hpp"

class Player;
class Bullet;

class World
{
private:
	int level = 1;
	int screenWidth, screenHeight;

public:
	MyVector2 center;

	World();
	World(int screenWidth, int screenHeight);

	int getScreenWidth();
	int getScreenHeight();

	void playerOnEdge(Player& player);
	void bulletOnEdge(Bullet& bullet);
};