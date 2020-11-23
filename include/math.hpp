#pragma once

#define FLT_EPSILON 1.19209290E-07F //constant for epsilon (number near 0)
#define M_PI 3.14159265358979323846

namespace Math
{
	float min(float a, float b);
	float max(float a, float b);

	float clamp(float val, float mini, float maxi);

	float toRadians(float angle);

	//returns randome float between min and max
	float random(int min, int max);
}