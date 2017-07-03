#include "render/resource/manager/resourceManager.h"
#include "render/object/entity/entity.h"

// Constructor
Entity::Entity(
    const char* name, vec3 _pos, vec3 _rot, float _scale, int _atlasPos
): pos(_pos), rot(_rot), scale(_scale), atlasPos(_atlasPos)
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
void Entity::incPos(float _x, float _y, float _z)
{
    pos.x += _x;
    pos.y += _y;
    pos.z += _z;
}

// Increase rotation
void Entity::incRot(float _pitch, float _yaw, float _roll)
{
    rot.x += _pitch;
    rot.y += _yaw;
    rot.z += _roll;
}

// Get entity position
vec3 Entity::getPos() const
{
    return pos;
}

// Get entity rotation
vec3 Entity::getRot() const
{
    return rot;
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

// Set entity position
void Entity::setPos(vec3 _pos)
{
    pos = _pos;
}

// Set entity rotation
void Entity::setRot(vec3 _rot)
{
    rot = _rot;
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
