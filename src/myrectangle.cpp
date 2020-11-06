#include "myrectangle.hpp"

MyRectangle::MyRectangle()
{
    center = {0.f, 0.f};
    width = 100;
    height = 100;
    angle = 0.f;
}

MyRectangle::MyRectangle(float x, float y, float width, float height)
{
    center = { x, y };
    this->width = width;
    this->height = height;
}

MyRectangle::operator Rectangle() const
{
    Rectangle newRect;
    newRect.x = center.x - width / 2;
    newRect.y = center.y - height / 2;
    newRect.width = width;
    newRect.height = height;
    return newRect;
}