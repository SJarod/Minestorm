#pragma once

#include "myvector2.hpp"
#include "myrectangle.hpp"
#include "mycircle.hpp"

namespace Collide
{
	// Point - Box
	bool    PointBox(MyVector2 p1, MyRectangle box);
	// Box - Box
	bool    BoxBox(MyRectangle& b1, MyRectangle& b2);
	// Circle - Box
	bool    CircleBox(MyCircle& c1, MyRectangle& box);
	// Point - Point
	bool    PointPoint(MyVector2 p1, MyVector2 p2);
	// Point - Circle
	bool    PointCircle(MyVector2 p1, MyCircle c1);
	// Circle - Circle
	bool    CircleCircle(MyCircle c1, MyCircle c2);
}