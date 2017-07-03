#include "utils/math/math.h"
#include "render/object/light/light.h"

// Constructor
Light::Light(
    vec3 _pos, vec3 _col, vec3 _att
): pos(_pos), col(_col), att(_att) {}

// Get light position
vec3 Light::getPos() const
{
    return pos;
}

// Get light color
vec3 Light::getCol() const
{
    return col;
}

// Get light attenuation factor
vec3 Light::getAtt() const
{
    return att;
}

// Calculate light attenuation
float Light::calcAttenuation(vec3 _pos) const
{
    float d = Math::distance(pos, _pos);
    return att.x + att.y * d + att.z * d * d;
}

// Set light position
void Light::setPos(vec3 _pos)
{
    pos = _pos;
}

// Set light color
void Light::setCol(vec3 _col)
{
    col = _col;
}

// Set light attenuation factor
void Light::setAtt(vec3 _att)
{
    att = _att;
}
