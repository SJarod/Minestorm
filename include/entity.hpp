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
	float				m_thrust;

	void draw(Color color) const;
};