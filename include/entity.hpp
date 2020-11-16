#pragma once

#include "raylib.h"

#include "myvector2.hpp"
#include "myreferential2.hpp"
#include "myconcavepolygon.hpp"

class Entity
{
private:

public:
	MyReferential2		m_local;
	MyConcavePolygon	m_shape;

	MyVector2			m_direction;	//direction vector
	MyVector2			m_speed;		//speed vector
	float				m_thrust = 100.f;

	//TODO : drift with
	//float				m_weight = 100.f;
	//float				m_kdrift = 0.5f;
	//float				m_friction = 0.5f;

	void draw(Color color) const;
};