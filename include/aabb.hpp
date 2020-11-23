#pragma once

#include <float.h>

#include "myvector2.hpp"

class AABB2
{
public:
	MyVector2 min = { FLT_MAX, FLT_MAX };
	MyVector2 max = { FLT_MIN, FLT_MIN };
};