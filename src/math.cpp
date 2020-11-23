#include "math.hpp"

#include <cmath>

float Math::min(float a, float b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

float Math::max(float a, float b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

float Math::clamp(float val, float mini, float maxi)
{
	return max(mini, min(val, maxi));
}

float Math::toRadians(float angle)
{
	return angle * M_PI / 180;
}

float Math::random(int min, int max)
{
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}