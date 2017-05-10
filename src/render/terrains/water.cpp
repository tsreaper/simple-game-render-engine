#include "../engine/loader.h"
#include "water.h"

// Size of a water terrain
const float Water::SIZE = 1024;

// Constructor
Water::Water(int _gridX, int _gridZ, float _y)
{
    // Set the coordinates
    gridX = _gridX; gridZ = _gridZ;
    x = gridX * SIZE; z = gridZ * SIZE;
    y = _y;
    
    float vertices[] = {
        0, y, 0,
        0, y, SIZE,
        SIZE, y, 0,
        SIZE, y, SIZE
    };
    
    raw = Loader::loadVertices("water", vertices, 12);
}

// Destructor
Water::~Water()
{
    delete raw;
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
RawModel* Water::getRaw() const
{
    return raw;
}
