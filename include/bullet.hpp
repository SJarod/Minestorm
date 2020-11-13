#pragma once

#include "entity.hpp"

#include "mycircle.hpp"

class Bullet : public Entity
{
private:

public:
	MyCircle m_shape;
};