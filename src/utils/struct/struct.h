#ifndef _STRUCT_H
#define _STRUCT_H

// 3D vector
struct vec3
{
    float x, y, z;
    vec3(float _x = 0, float _y = 0, float _z = 0): x(_x), y(_y), z(_z) {}
    vec3 operator-() const
    {
        vec3 ret;
        ret.x = -x; ret.y = -y; ret.z = -z;
        return ret;
    }
};

#endif
