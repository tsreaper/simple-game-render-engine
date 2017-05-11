#ifndef WATER_H_
#define WATER_H_

#include "../models/rawModel.h"
#include "../textures/modelTexture.h"

// Water
class Water
{
public:
    
    // Size of a water terrain
    static const float SIZE;
    
    // DUDV map file
    static const char* DUDV_FILE;
    
    // Constructor
    Water(int _gridX, int _gridZ, float _y);
    
    // Destructor
    ~Water();
    
    // Get X coordinate
    float getX() const;
    
    // Get Y coordinate
    float getY() const;
    
    // Get Z coordinate
    float getZ() const;
    
    // Get grid-X coordinate
    int getGridX() const;
    
    // Get grid-Z coordinate
    int getGridZ() const;
    
    // Get raw model
    RawModel* getRaw() const;
    
    // Get dudv map texture
    ModelTexture* getDudv() const;
    
private:
    
    // Position of the water
    float x, y, z;
    
    // Grid coordinates of the water
    int gridX, gridZ;
    
    // Raw model (a quad) of the water
    RawModel* raw;
    
    // DUDV map
    ModelTexture* dudv;
};

#endif
