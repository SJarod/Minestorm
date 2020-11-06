#pragma once

#include <raylib.h>

#include "myvector2.hpp"

class MyRectangle
{
public:
    MyVector2   center;
    float       width;
    float       height;

    MyRectangle();
    MyRectangle(float x, float y, float width, float height);

    operator Rectangle() const;
};