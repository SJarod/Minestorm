#pragma once

#include <raylib.h>

#include "myvector2.hpp"

class MyRectangle
{
public:
    MyVector2   center;
    float       width;
    float       height;
    float       angle;

    MyRectangle();
    MyRectangle(float x, float y, float width, float height);

    operator Rectangle() const;
};