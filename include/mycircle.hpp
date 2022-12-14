#pragma once

#include "myvector2.hpp"

class MyCircle
{
public:
    MyCircle() = default;
    MyCircle(MyVector2 c, float r);

    MyVector2   center;
    float       radius;
};