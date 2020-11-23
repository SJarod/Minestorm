#pragma once

#include "raylib.h"

#include "entity.hpp"
#include "bullet.hpp"

#include "myconvexpolygon.hpp"

class World;

struct PlayerInput
{
	bool	movingForward;
	bool	rotateRight;
	bool	rotateLeft;
	bool	shooting;
	bool	teleporting;
};

class Player : public Entity
{
private:
	int m_id = 1;
	int	m_health = 3;

	MyVector2 m_pos;

public:
	Color m_color = { 128, 128, 255, 255 };

	PlayerInput			m_inputs;
	std::vector<Bullet> m_bullet;
	float				m_shootingTime = 0.f;

	Player();
	Player(MyVector2 pos);
	~Player();

	int getId() const;
	int getHealth() const;
	void addHealth();
	
	void setSecondPlayer();
	void setInputs();

	void shoot(float currentTime);
	bool isHit();
	void move(World& game, float deltaTime);
	void update(float deltaTime, float gameSpeed);
};