#include <raylib.h>

#include <cmath>

#include "math.hpp"
#include "myconvexpolygon.hpp"

MyConvexPolygon::MyConvexPolygon()
{

}

MyConvexPolygon::MyConvexPolygon(MyVector2* ptr)
{
	center = { 0.f, 0.f };
	points = ptr;
}