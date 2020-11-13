#include <iostream>

#include "myreferential2.hpp"
#include "myvector2.hpp"

void MyReferential2::rotateReferential(float rotation)
{
    ui = ui.vectorRotation(rotation);
    uj = uj.vectorRotation(rotation);
}

MyVector2 MyReferential2::posLocalGlobal(MyVector2 localPos)
{
    //return localPos + origin;

    MyVector2 globalPos;
    globalPos = origin.addVector(ui.scaleVector(localPos.x));
    globalPos = globalPos.addVector(uj.scaleVector(localPos.y));

    return globalPos;
}

MyVector2 MyReferential2::posGlobalLocal(MyVector2 globalPos)
{
    MyVector2 localPos;

    MyVector2 temp;
    temp.x = globalPos.x - origin.x;
    temp.y = globalPos.y - origin.y;

    localPos.x = temp.dotProduct(ui);
    localPos.y = temp.dotProduct(uj);

    return localPos;
}

MyVector2 MyReferential2::vectorLocalGlobal(MyVector2 localVect)
{
    MyVector2 globalVect;
    globalVect = ui.scaleVector(localVect.x).addVector(uj.scaleVector(localVect.y));

    return globalVect;
}

MyVector2 MyReferential2::vectorGlobalLocal(MyVector2 globalVect)
{
    MyVector2 localVect;

    localVect.x = globalVect.dotProduct(ui);
    localVect.y = globalVect.dotProduct(uj);

    return localVect;
}