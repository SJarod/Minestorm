#pragma once

#include "entity.hpp"

#include "myvector2.hpp"
#include "myconvexpolygon.hpp"

class World;

class Enemy : public Entity
{
private:

protected:
	MyVector2	m_spawnPoint;

public:
	Enemy();
	Enemy(World& game);
	virtual ~Enemy();

	void drawSpawnPoint();
	void spawn();

	virtual void move(World& game, float deltaTime);
};

class FloatingMine : public Enemy
{
private:

public:
	FloatingMine();
	FloatingMine(World& game);
};

class FireballMine : public Enemy
{
private:

public:
	FireballMine();
	FireballMine(World& game);
};

class MagneticMine : public Enemy
{
private:

public:
	MagneticMine();
	MagneticMine(World& game);

	void move(World& game, float deltaTime) override;
};

class MagneticFireballMine : public Enemy
{
private:

public:
	MagneticFireballMine();
	MagneticFireballMine(World& game);

	void move(World& game, float deltaTime) override;
};

class Fireball : public Enemy
{
private:

public:
	Fireball();
	Fireball(World& game);
};

class Minelayer : public Enemy
{
private:

public:
	Minelayer();
	Minelayer(World& game);
};