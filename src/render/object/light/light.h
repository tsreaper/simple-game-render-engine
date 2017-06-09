#ifndef _LIGHT_H
#define _LIGHT_H

// Light source
class Light
{
public:

    // Constructor
    Light(float _x, float _y, float _z, float _r, float _g, float _b, float _att0 = 1, float _att1 = 0, float _att2 = 0);

    // Get X coordinate
    float getX() const;

    // Get Y coordinate
    float getY() const;

    // Get Z coordinate
    float getZ() const;

    // Get red component
    float getR() const;

    // Get green component
    float getG() const;

    // Get blue component
    float getB() const;

    // Get attenuation factor 0
    float getAtt0() const;

    // Get attenuation factor 1
    float getAtt1() const;

    // Get attenuation factor 2
    float getAtt2() const;

    // Get light attenuation factor
    float calcAttenuation(float _x, float _y, float _z) const;

    // Set X coordinate
    void setX(float _x);

    // Set Y coordinate
    void setY(float _y);

    // Set Z coordinate
    void setZ(float _z);

    // Set red component
    void setR(float _r);

    // Set green component
    void setG(float _g);

    // Set blue component
    void setB(float _b);

    // Set light attenuation factor
    void setAttenuation(float _att0, float _att1, float _att2);

private:

    // XYZ positions
    float x, y, z;

    // RGB components
    float r, g, b;

    // Attenuation components
    float att0, att1, att2;
};

#endif
