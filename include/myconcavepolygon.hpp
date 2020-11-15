#pragma once

#include "myconvexpolygon.hpp"

#include <vector>

class MyConcavePolygon
{
public:
	//TODO : array of points
	//TODO : array of convex polygons that take points of the array (of points)
	std::vector<MyConvexPolygon>	polygons;	//array of convex polygons

	MyConcavePolygon();

	MyConcavePolygon operator=(MyConvexPolygon convex);
};