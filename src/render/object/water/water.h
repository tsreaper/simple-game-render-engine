#ifndef _WATER_H
#define _WATER_H

#include "../../resource/model/rawModel.h"
#include "../../resource/texture/plainTexture.h"

// Water
class Water
{
public:

    // Size of a water terrain
    static const float SIZE;

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
    RawModel* getModel() const;

    // Get DUDV map
    PlainTexture* getDudv() const;

    // Get normal map
    PlainTexture* getNorm() const;

    // Set Y coordinate
    void setY(float _y);

private:

    // Grid coordinates of the water
    int gridX, gridZ;

    // Position of the water
    float x, y, z;

    // Raw model (a quad) of the water
    RawModel* model;

    // DUDV map
    PlainTexture* dudv;

    // Normal map
    PlainTexture* norm;
};

#endif
