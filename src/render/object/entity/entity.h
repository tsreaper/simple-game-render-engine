#ifndef _ENTITY_H
#define _ENTITY_H

#include "utils/struct/struct.h"

#include "render/resource/model/rawModel.h"
#include "render/resource/texture/modelTexture.h"

// Entity in the 3D world
class Entity
{
public:

    // Constructor
    Entity(
        const char* name, vec3 _pos = vec3(0, 0, 0),
        vec3 _rot = vec3(0, 0, 0), float _scale = 1, int _atlasPos = 0
    );

    // Destructor
    ~Entity();

    // Increase position
    void incPos(float _x, float _y, float _z);

    // Increase rotation
    void incRot(float _pitch, float _yaw, float _roll);

    // Get entity position
    vec3 getPos() const;

    // Get entity rotation
    vec3 getRot() const;

    // Get scaling factor
    float getScale() const;

    // Get position in atlas
    int getAtlasPos() const;

    // Get raw model
    RawModel* getModel() const;

    // Get model texture
    ModelTexture* getTexture() const;

    // Set entity position
    void setPos(vec3 _pos);

    // Set entity rotation
    void setRot(vec3 _rot);

    // Set scaling factor
    void setScale(float _scale);

    // Set position in atlas
    void setAtlasPos(int _atlasPos);

private:

    // Entity position
    vec3 pos;

    // Entity rotation
    vec3 rot;

    // Scaling factor
    float scale;

    // Texture position in an atlas
    int atlasPos;

    // Entity raw model
    RawModel* model;

    // Entity texture
    ModelTexture* texture;
};

#endif
