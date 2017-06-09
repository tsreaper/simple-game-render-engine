#include "render/resource/manager/resourceManager.h"
#include "render/object/entity/entity.h"

// Constructor
Entity::Entity(
    const char* name, float _tX, float _tY, float _tZ,
    float _rX, float _rY, float _rZ, float _scale, int _atlasPos
): tX(_tX), tY(_tY), tZ(_tZ), rX(_rX), rY(_rY), rZ(_rZ), scale(_scale), atlasPos(_atlasPos)
{
    model = ResourceManager::getResource<RawModel>(name);
    texture = ResourceManager::getResource<ModelTexture>(name);
}

// Destructor
Entity::~Entity()
{
    ResourceManager::deleteResource<RawModel>(model);
    ResourceManager::deleteResource<ModelTexture>(texture);
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

// Get raw model
RawModel* Entity::getModel() const
{
    return model;
}

// Get model texture
ModelTexture* Entity::getTexture() const
{
    return texture;
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

// Get position in atlas
int Entity::getAtlasPos() const
{
    return atlasPos;
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

// Set position in atlas
void Entity::setAtlasPos(int _atlasPos)
{
    atlasPos = _atlasPos;
}
