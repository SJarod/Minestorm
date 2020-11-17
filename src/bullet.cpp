#include "bullet.hpp"

Bullet::Bullet()
{

}

Bullet::Bullet(MyVector2 c, MyVector2 dir, float lifeTime)
{
	m_shape.center = c;
	m_shape.radius = 5.f;

	m_lifeTime = lifeTime;

	m_direction = dir;
}

void Bullet::move(float deltaTime, float gameSpeed)
{
	m_shape.center += m_direction * 10 * deltaTime * gameSpeed;
}

void Bullet::draw(Color color) const
{
	DrawCircle(m_shape.center.x, m_shape.center.y, m_shape.radius, color);
}