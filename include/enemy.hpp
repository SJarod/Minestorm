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

	void			divide(World& game);
};

class FloatingMine : public Enemy
{
private:

public:
	FloatingMine();
	FloatingMine(World& game, EnemySize size);
};

class FireballMine : public Enemy
{
private:

public:
	FireballMine();
	FireballMine(World& game, EnemySize size);

	bool shoot();
};

class MagneticMine : public Enemy
{
private:

public:
	MagneticMine();
	MagneticMine(World& game, EnemySize size);

	void move(World& game, float deltaTime) override;
};

class MagneticFireballMine : public Enemy
{
private:

public:
	MagneticFireballMine();
	MagneticFireballMine(World& game, EnemySize size);

	void move(World& game, float deltaTime) override;

	bool shoot();
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

public:
	Minelayer();
	Minelayer(World& game);
};