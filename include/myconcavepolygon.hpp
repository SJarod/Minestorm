#pragma once

#include "myconvexpolygon.hpp"

#include <vector>

class MyConcavePolygon
{
public:
	MyVector2*						points;
	std::vector<MyConvexPolygon>	polygons;	//array of convex polygons

	MyConcavePolygon();

	MyConcavePolygon operator=(MyConvexPolygon convex);
};