#include "render/resource/manager/resourceManager.h"
#include "render/resource/model/geometricModel.h"

#include "render/object/water/water.h"

// Size of a water terrain
const float Water::SIZE = 1024;

// Constructor
Water::Water(int _gridX, int _gridZ, float _y): gridX(_gridX), gridZ(_gridZ), y(_y)
{
    // Set the coordinates
    x = gridX * SIZE; z = gridZ * SIZE;

    // Set model and texture
    model = GeometricModel::getGeometricModel(GeometricModel::SQUARE_XZ);
    dudv = ResourceManager::getResource<PlainTexture>("waterDudv");
    norm = ResourceManager::getResource<PlainTexture>("waterNorm");
}

// Destructor
Water::~Water()
{
    ResourceManager::deleteResource<PlainTexture>(dudv);
    ResourceManager::deleteResource<PlainTexture>(norm);
}

// Get X coordinate
float Water::getX() const
{
    return x;
}

// Get Y coordinate
float Water::getY() const
{
    return y;
}

// Get Z coordinate
float Water::getZ() const
{
    return z;
}

// Get grid-X coordinate
int Water::getGridX() const
{
    return gridX;
}

// Get grid-Z coordinate
int Water::getGridZ() const
{
    return gridZ;
}

// Get raw model
RawModel* Water::getModel() const
{
    return model;
}

// Get DUDV map
PlainTexture* Water::getDudv() const
{
    return dudv;
}

// Get normal map
PlainTexture* Water::getNorm() const
{
    return norm;
}

// Set Y coordinate
void Water::setY(float _y)
{
    y = _y;
}
