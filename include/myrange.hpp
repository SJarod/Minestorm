#pragma once

#include "myvector2.hpp"
#include "myrectangle.hpp"
#include "mycircle.hpp"
#include "myconvexpolygon.hpp"

class MyRange
{
public:
    float   min;
    float   max;

    //initialize range to the value
    void rangeInit(float value);

    //returns range of 2 ranges
    MyRange mergeRange(MyRange range);

    //add a value to the range
    void rangeAddValue(float value);

    //check if the 2 ranges are colliding
    bool rangeCollision(MyRange range);

    //range : point
    MyRange rangePoint(MyVector2 point, MyVector2 dir);
    //range : rectangle
    MyRange rangeRectangle(MyRectangle rect, MyVector2 dir);
    //range : circle
    MyRange rangeCircle(MyCircle circle, MyVector2 dir);
    //range : convex polygon
    MyRange rangeConvex(MyConvexPolygon poly, MyVector2 dir);
};