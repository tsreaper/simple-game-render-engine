#ifndef _CAMERA_H
#define _CAMERA_H

#include "utils/struct/struct.h"

// Camera of the 3D world
class Camera
{
public:

    // Increase position
    static void incPos(float _x, float _y, float _z);

    // Increase rotation
    static void incRot(float _pitch, float _yaw, float _roll);

    // Get camera position
    static vec3 getPos();

    // Get camera rotation
    static vec3 getRot();

    // Set camera position
    static void setPos(vec3 _pos);

    // Set camera rotation
    static void setRot(vec3 _rot);

private:

    // Camera position
    static vec3 pos;

    // Camera rotation
    static vec3 rot;
};

#endif
