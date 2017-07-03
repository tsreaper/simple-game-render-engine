#ifndef _WATER_H
#define _WATER_H

#include "utils/struct/struct.h"

#include "render/resource/model/rawModel.h"
#include "render/resource/texture/plainTexture.h"

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

    // Get water position
    vec3 getPos() const;

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

    // Water position
    vec3 pos;

    // Raw model (a quad) of the water
    RawModel* model;

    // DUDV map
    PlainTexture* dudv;

    // Normal map
    PlainTexture* norm;
};

#endif
