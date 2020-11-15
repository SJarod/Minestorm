#pragma once

#include "raylib.h"

#include "world.hpp"
#include "entity.hpp"
#include "bullet.hpp"

#include "myconvexpolygon.hpp"

struct InputPlayerOne
{
	int		movingForward = IsKeyDown(KEY_R);
	float	rotateRight = IsKeyDown(KEY_G);
	float	rotateLeft = IsKeyDown(KEY_D);
	int		shooting = IsKeyDown(KEY_F);
};

struct InputPlayerTwo
{
	int		movingForward = IsKeyDown(KEY_I);
	float	rotateRight = IsKeyDown(KEY_L);
	float	rotateLeft = IsKeyDown(KEY_J);
	int		shooting = IsKeyDown(KEY_K);
};

class Player : public Entity
{
private:
	int					m_health = 3;

public:
	std::vector<Bullet> m_bullet;

	Player();
	Player(World game);
	~Player();
	
	void shoot(float currentTime);
	void move(World game, float deltaTime);
	void teleport(World game);
	void update(float deltaTime);
};