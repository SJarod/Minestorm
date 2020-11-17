#pragma once

#include "myvector2.hpp"

#include "player.hpp"
#include "enemy.hpp"

#include <vector>

class Bullet;

class World
{
private:
	int level = 1;
	int screenWidth, screenHeight;

public:
	MyVector2	m_center;
	float		m_gameSpeed;

	std::vector<Player> m_players;
	std::vector<Enemy>	m_enemies;

	World();
	World(int screenWidth, int screenHeight);

	int getScreenWidth();
	int getScreenHeight();

	//TODO : remove all parameters for OnEdge function (for player and enemy), already in the object game
	void playerOnEdge(Player& player);
	void bulletOnEdge(Bullet& bullet);
	void enemyOnEdge(Enemy& enemy);
};