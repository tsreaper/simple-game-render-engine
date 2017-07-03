#ifndef _LIGHT_H
#define _LIGHT_H

#include "utils/struct/struct.h"

// Light source
class Light
{
public:

    // Constructor
    Light(vec3 _pos, vec3 _col, vec3 _att);

    // Get light position
    vec3 getPos() const;

    // Get light color
    vec3 getCol() const;

    // Get light attenuation factor
    vec3 getAtt() const;

    // Calculate light attenuation
    float calcAttenuation(vec3 _pos) const;

    // Set light position
    void setPos(vec3 _pos);

    // Set light color
    void setCol(vec3 _col);

    // Set light attenuation factor
    void setAtt(vec3 _att);

private:

    // Light position
    vec3 pos;

    // Light color
    vec3 col;

    // Light attenuation factor
    vec3 att;
};

#endif
