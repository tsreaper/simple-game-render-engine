#include "../engine/memoryManager.h"
#include "entity.h"

// Constructor
Entity::Entity(TexturedModel* _model)
{
    model = _model;
    tX = tY = tZ = 0;
    rX = rY = rZ = 0;
    scale = 1;
}

// Destructor
Entity::~Entity()
{
    MemoryManager::deleteTexturedModel(model);
}

// Increase position
void Entity::incPosition(float x, float y, float z)
{
    tX += x;
    tY += y;
    tZ += z;
}

// Increase rotation
void Entity::incRotation(float x, float y, float z)
{
    rX += x;
    rY += y;
    rZ += z;
}

// Get model
TexturedModel* Entity::getModel() const
{
    return model;
}

// Get X coordinate
float Entity::getTX() const
{
    return tX;
}

// Get Y coordinate
float Entity::getTY() const
{
    return tY;
}

// Get Z coordinate
float Entity::getTZ() const
{
    return tZ;
}

// Get X rotation
float Entity::getRX() const
{
    return rX;
}

// Get Y rotation
float Entity::getRY() const
{
    return rY;
}

// Get Z rotation
float Entity::getRZ() const
{
    return rZ;
}

// Get scaling factor
float Entity::getScale() const
{
    return scale;
}

// Set X coordinate
void Entity::setTX(float _tX)
{
    tX = _tX;
}

// Set Y coordinate
void Entity::setTY(float _tY)
{
    tY = _tY;
}

// Set Z coordinate
void Entity::setTZ(float _tZ)
{
    tZ = _tZ;
}

// Set X rotation
void Entity::setRX(float _rX)
{
    rX = _rX;
}

// Set Y rotation
void Entity::setRY(float _rY)
{
    rY = _rY;
}

// Set Z rotation
void Entity::setRZ(float _rZ)
{
    rZ = _rZ;
}

// Set scaling factor
void Entity::setScale(float _scale)
{
    scale = _scale;
}
