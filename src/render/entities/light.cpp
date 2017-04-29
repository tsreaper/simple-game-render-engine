#include "light.h"

// Constructor
Light::Light(float _x, float _y, float _z, float _r, float _g, float _b)
{
    x = _x; y = _y; z = _z;
    r = _r; g = _g; b = _b;
}

// Get X coordinate
float Light::getX() const
{
    return x;
}

// Get Y coordinate
float Light::getY() const
{
    return y;
}

// Get Z coordinate
float Light::getZ() const
{
    return z;
}

// Get red component
float Light::getR() const
{
    return r;
}

// Get green component
float Light::getG() const
{
    return g;
}

// Get blue component
float Light::getB() const
{
    return b;
}

// Set X coordinate
void Light::setX(float _x)
{
    x = _x;
}

// Set Y coordinate
void Light::setY(float _y)
{
    y = _y;
}

// Set Z coordinate
void Light::setZ(float _z)
{
    z = _z;
}

// Set red component
void Light::setR(float _r)
{
    r = _r;
}

// Set green component
void Light::setG(float _g)
{
    g = _g;
}

// Set blue component
void Light::setB(float _b)
{
    b = _b;
}
