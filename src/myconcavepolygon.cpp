#include "myconcavepolygon.hpp"

MyConcavePolygon MyConcavePolygon::operator=(MyConvexPolygon convex)
{
	polygons.push_back(convex);

	return *this;
}