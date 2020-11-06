#pragma once

#include "myvector2.hpp"

class MyConvexPolygon
{
public:
    MyVector2* points;    //array of points

    MyConvexPolygon();

    void draw();
};