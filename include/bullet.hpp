#pragma once

#include "raylib.h"

#include "mycircle.hpp"

class Bullet
{
private:

public:
	MyCircle	m_shape;
	float		m_lifeTime;

	MyVector2	m_direction;

	Bullet();
	Bullet(MyVector2 c, MyVector2 dir, float lifeTime);

	void move(float deltaTime);

	void draw(Color color) const;
};