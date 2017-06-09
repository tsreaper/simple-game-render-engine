#include "utils/math/math.h"
#include "render/object/light/light.h"

// Constructor
Light::Light(
    float _x, float _y, float _z, float _r, float _g, float _b, float _att0, float _att1, float _att2
): x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), att0(_att0), att1(_att1), att2(_att2) {}

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

// Get attenuation factor 0
float Light::getAtt0() const
{
    return att0;
}

// Get attenuation factor 1
float Light::getAtt1() const
{
    return att1;
}

// Get attenuation factor 2
float Light::getAtt2() const
{
    return att2;
}

// Calculate light attenuation factor
float Light::calcAttenuation(float _x, float _y, float _z) const
{
    float p[3], q[3];
    p[0] = _x; p[1] = _y; p[2] = _z;
    q[0] = x; q[1] = y; q[2] = z;

    float d = Math::distance(p, q, 3);
    return att0 + att1 * d + att2 * d * d;
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

// Set attenuation factor
void Light::setAttenuation(float _att0, float _att1, float _att2)
{
    att0 = _att0;
    att1 = _att1;
    att2 = _att2;
}
