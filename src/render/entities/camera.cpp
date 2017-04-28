#include "camera.h"

// Positions of camera
float Camera::x = 0;
float Camera::y = 0;
float Camera::z = 0;

// Rotations of camera
float Camera::pitch = 0;
float Camera::yaw = 0;
float Camera::roll = 0;

// Increase position
void Camera::incPosition(float _x, float _y, float _z)
{
    x += _x;
    y += _y;
    z += _z;
}

// Increase rotation
void Camera::incRotation(float _pitch, float _yaw, float _roll)
{
    pitch += _pitch;
    yaw += _yaw;
    roll += _roll;
}

// Get X coordinate
float Camera::getX()
{
    return x;
}

// Get Y coordinate
float Camera::getY()
{
    return y;
}

// Get Z coordinate
float Camera::getZ()
{
    return z;
}

// Get pitch
float Camera::getPitch()
{
    return pitch;
}

// Get yaw
float Camera::getYaw()
{
    return yaw;
}

// Get roll
float Camera::getRoll()
{
    return roll;
}

// Set X coordinate
void Camera::setX(float _x)
{
    x = _x;
}

// Set Y coordinate
void Camera::setY(float _y)
{
    y = _y;
}

// Set Z coordinate
void Camera::setZ(float _z)
{
    z = _z;
}

// Set pitch
void Camera::setPitch(float _pitch)
{
    pitch = _pitch;
}

// Set yaw
void Camera::setYaw(float _yaw)
{
    yaw = _yaw;
}

// Set roll
void Camera::setRoll(float _roll)
{
    roll = _roll;
}
