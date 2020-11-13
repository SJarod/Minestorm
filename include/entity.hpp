#pragma once

#include "myvector2.hpp"
#include "myreferential2.hpp"

class Entity
{
private:

public:
	MyReferential2	local;

	MyVector2		direction;	//direction vector
	float			thrust;

	virtual void draw() const;
};