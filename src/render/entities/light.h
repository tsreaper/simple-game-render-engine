#ifndef LIGHT_H_
#define LIGHT_H_

// Light source
class Light
{
public:
    
    // Constructor
    Light(float _x, float _y, float _z, float _r, float _g, float _b);
    
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
    
private:
    
    // XYZ positions
    float x, y, z;
    
    // RGB components
    float r, g, b;
};

#endif
