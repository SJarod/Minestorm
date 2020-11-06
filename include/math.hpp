#pragma once

#define M_PI 3.14159265358979323846

namespace Math
{
	float min(float a, float b);
	float max(float a, float b);

	float clamp(float val, float mini, float maxi);
}