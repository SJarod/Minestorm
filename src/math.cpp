#include "math.hpp"

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