#include "render/object/camera/camera.h"

// Camera position
vec3 Camera::pos = vec3(0, 0, 0);

// Rotations of camera
vec3 Camera::rot = vec3(0, 0, 0);

// Increase position
void Camera::incPos(float _x, float _y, float _z)
{
    pos.x += _x;
    pos.y += _y;
    pos.z += _z;
}

// Increase rotation
void Camera::incRot(float _pitch, float _yaw, float _roll)
{
    rot.x += _pitch;
    rot.y += _yaw;
    rot.z += _roll;
}

// Get camera position
vec3 Camera::getPos()
{
    return pos;
}

// Get camera rotation
vec3 Camera::getRot()
{
    return rot;
}

// Set camera position
void Camera::setPos(vec3 _pos)
{
    pos = _pos;
}

// Set camera rotation
void Camera::setRot(vec3 _rot)
{
    rot = _rot;
}
