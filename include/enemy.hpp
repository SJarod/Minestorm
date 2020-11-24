#pragma once

#include "entity.hpp"

#include "myvector2.hpp"
#include "myconvexpolygon.hpp"
#include "mycircle.hpp"

class World;
class Fireball;

enum EnemySize
{
	SMALL,
	MEDIUM,
	BIG,
};

class Enemy : public Entity
{
private:

protected:
	EnemySize m_size;

public:

	Enemy();
	Enemy(World& game);
	virtual ~Enemy();

	virtual void	move(World& game, float deltaTime);
	virtual bool	shoot();
	virtual void	addScore(int& score);

	void			divide(World& game);
};

class FloatingMine : public Enemy
{
private:

public:
	FloatingMine();
	FloatingMine(World& game, EnemySize size);

	void addScore(int& score);
};

class FireballMine : public Enemy
{
private:

public:
	FireballMine();
	FireballMine(World& game, EnemySize size);

	bool shoot();
	void addScore(int& score);
};

class MagneticMine : public Enemy
{
private:

public:
	MagneticMine();
	MagneticMine(World& game, EnemySize size);

	void move(World& game, float deltaTime) override;
	void addScore(int& score);
};

class MagneticFireballMine : public Enemy
{
private:

public:
	MagneticFireballMine();
	MagneticFireballMine(World& game, EnemySize size);

	void	move(World& game, float deltaTime) override;

	bool	shoot();
	void	addScore(int& score);
};

class Fireball
{
private:

public:
	MyCircle	m_shape;
	float		m_lifeTime;

	MyVector2	m_direction;

	Fireball();
	Fireball(MyVector2 c, MyVector2 dir, float lifeTime);

	void move(float deltaTime, float gameSpeed);

	void draw(Color color) const;
};

class Minelayer : public Enemy
{
private:
	MyVector2	m_spawnPoint;
	bool		m_arrived = false;

public:
	Minelayer();
	Minelayer(World& game);

	void move(World& game, float deltaTime) override;
	void arrived(World& game);

	void addScore(int& score);
};