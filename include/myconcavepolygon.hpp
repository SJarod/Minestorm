#pragma once

#include "myconvexpolygon.hpp"

#include <vector>

class MyConcavePolygon
{
public:
	std::vector<MyConvexPolygon> polygons;	//array of convex polygons

	MyConcavePolygon();

	MyConcavePolygon operator=(MyConvexPolygon convex);
};