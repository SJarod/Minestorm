#pragma once

#include "entity.hpp"

#include "myvector2.hpp"
#include "myconvexpolygon.hpp"
#include "world.hpp"

class Enemy : public Entity
{
private:

protected:
	MyVector2 m_spawnPoint;

public:
	Enemy();
	Enemy(World game);
	~Enemy();

	void drawSpawnPoint();
};

class FloatingMine : public Enemy
{
private:

public:
};

class FireballMine : public Enemy
{
private:

public:
};

class MagneticMine : public Enemy
{
private:

public:
};

class MagneticFireballMine : public Enemy
{
private:

public:
};

class Fireball : public Enemy
{
private:

public:
};

class Minelayer : public Enemy
{
private:

public:
};