#pragma once

#include "myvector2.hpp"
#include "myreferential2.hpp"
#include "myconcavepolygon.hpp"

class Entity
{
private:

public:
	MyReferential2	local;
	MyConcavePolygon shape;

	MyVector2		direction;	//direction vector
	float			thrust;

	void draw() const;
};