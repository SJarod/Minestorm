#pragma once

#include "myvector2.hpp"

class MyConvexPolygon
{
public:
    MyVector2   center;

    MyVector2*  points;    //array of points
    int         count;

    float       angle;

    MyConvexPolygon();
    MyConvexPolygon(MyVector2* ptr);
};