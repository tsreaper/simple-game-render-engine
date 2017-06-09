#ifndef _ENTITY_H
#define _ENTITY_H

#include "render/resource/model/rawModel.h"
#include "render/resource/texture/modelTexture.h"

// Entity in the 3D world
class Entity
{
public:

    // Constructor
    Entity(
        const char* name, float _tX = 0, float _tY = 0, float _tZ = 0,
        float _rX = 0, float _rY = 0, float _rZ = 0, float _scale = 1, int _atlasPos = 0
    );

    // Destructor
    ~Entity();

    // Increase position
    void incPosition(float x, float y, float z);

    // Increase rotation
    void incRotation(float x, float y, float z);

    // Get raw model
    RawModel* getModel() const;

    // Get model texture
    ModelTexture* getTexture() const;

    // Get X coordinate
    float getTX() const;

    // Get Y coordinate
    float getTY() const;

    // Get Z coordinate
    float getTZ() const;

    // Get X rotation
    float getRX() const;

    // Get Y rotation
    float getRY() const;

    // Get Z rotation
    float getRZ() const;

    // Get scaling factor
    float getScale() const;

    // Get position in atlas
    int getAtlasPos() const;

    // Set X coordinate
    void setTX(float _tX);

    // Set Y coordinate
    void setTY(float _tY);

    // Set Z coordinate
    void setTZ(float _tZ);

    // Set X rotation
    void setRX(float _rX);

    // Set Y rotation
    void setRY(float _rY);

    // Set Z rotation
    void setRZ(float _rZ);

    // Set scaling factor
    void setScale(float _scale);

    // Set position in atlas
    void setAtlasPos(int _atlasPos);

private:

    // Entity raw model
    RawModel* model;

    // Entity texture
    ModelTexture* texture;

    // XYZ coordinates
    float tX, tY, tZ;

    // XYZ rotations
    float rX, rY, rZ;

    // Scaling factor
    float scale;

    // Texture position in an atlas
    int atlasPos;
};

#endif
