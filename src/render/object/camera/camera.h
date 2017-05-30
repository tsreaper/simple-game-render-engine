#ifndef _CAMERA_H
#define _CAMERA_H

// Camera of the 3D world
class Camera
{
public:

    // Increase position
    static void incPosition(float _x, float _y, float _z);

    // Increase rotation
    static void incRotation(float _pitch, float _yaw, float _roll);

    // Get X coordinate
    static float getX();

    // Get Y coordinate
    static float getY();

    // Get Z coordinate
    static float getZ();

    // Get pitch
    static float getPitch();

    // Get yaw
    static float getYaw();

    // Get roll
    static float getRoll();

    // Set X coordinate
    static void setX(float _x);

    // Set Y coordinate
    static void setY(float _y);

    // Set Z coordinate
    static void setZ(float _z);

    // Set pitch
    static void setPitch(float _pitch);

    // Set yaw
    static void setYaw(float _yaw);

    //Set roll
    static void setRoll(float _roll);

private:

    // Positions of camera
    static float x, y, z;

    // Rotations of camera
    static float pitch, yaw, roll;
};

#endif
