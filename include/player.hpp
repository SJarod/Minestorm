#pragma once

#include "world.hpp"
#include "entity.hpp"

#include "myconvexpolygon.hpp"

class Player : public Entity
{
private:
	int	m_health = 3;

public:
	MyConvexPolygon shape;

	Player();
	Player(World game);
	~Player();

	void move();
	void update();

	void draw() const override;
};