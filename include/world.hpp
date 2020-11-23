#pragma once

#include "myvector2.hpp"

#include "player.hpp"
#include "enemy.hpp"

#include <vector>

class Bullet;

enum GameMode
{
	MENU,
	ONE,
	TWO,
	OVER
};

class World
{
private:
	int m_level = 1;
	int m_score;
	int screenWidth, screenHeight;

public:
	MyVector2	m_center;
	float		m_gameSpeed;
	GameMode	m_menu = MENU;

	int						m_playerCount = 1;
	std::vector<Player*>	m_players;
	std::vector<Enemy*>		m_enemies;

	World();
	World(int screenWidth, int screenHeight);
	~World();

	int getScreenWidth(int dif);
	int getScreenHeight(int dif);

	void displayMenu();
	void displayHUD();
	void displayGameOver();

	void gameLoopSingleplayer(float deltaTime, float currentTime);
	void gameLoopMultiplayer(float deltaTime, float currentTime);

	void playerOnEdge();
	void bulletOnEdge();
	void enemyOnEdge();
};