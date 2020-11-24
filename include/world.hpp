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
	OVER,
};

class World
{
private:
	int m_level;
	int m_score;
	int screenWidth, screenHeight;

public:
	MyVector2	m_center;
	MyVector2	m_corners[4];

	float		m_gameSpeed;
	GameMode	m_menu = MENU;

	int			m_spawnNum;
	float		m_spawnTime = 0.f;
	int			m_enemyNum = 2;
	int			m_minelayerNum = 1;

	int						m_playerCount = 1;
	std::vector<Player*>	m_players;

	std::vector<Enemy*>		m_enemies;
	std::vector<Fireball>   m_fireballs;

	MyVector2*				m_spawnPoint;

	World();
	World(int screenWidth, int screenHeight);
	~World();

	int getScreenWidth(int dif);
	int getScreenHeight(int dif);


	void displayMenu();
	void displayHUD();
	void displayPause();
	void displayGameOver();


	void setGame();
	void endGame();

	void nextLevel();

	void playerLoop(float deltaTime, float currentTime);
	void movingLoop(float deltaTime);
	void playerDraw();

	void drawSpawnPoint();
	void spawn(EnemySize size);
	void spawnMinelayer();

	void playerOnEdge();
	void bulletOnEdge();
	void fireballOnEdge();
	void enemyOnEdge();
	void entitiesOnEdge();


	void gameLoopSingleplayer(float deltaTime, float currentTime);
	void gameLoopMultiplayer(float deltaTime, float currentTime);
};