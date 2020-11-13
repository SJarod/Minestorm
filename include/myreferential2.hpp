#pragma once

#include "myvector2.hpp"

class MyReferential2
{
public:
    MyVector2   origin;
    MyVector2   ui, uj; //unit vectors for referential
    float       angle;

    void rotateReferential(float rotation);

    //changes referential
    MyVector2 posLocalGlobal(MyVector2 localPos);
    MyVector2 posGlobalLocal(MyVector2 globalPos);

    MyVector2 vectorLocalGlobal(MyVector2 localVect);
    MyVector2 vectorGlobalLocal(MyVector2 globalVect);
};