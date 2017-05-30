#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "../../resource/model/rawModel.h"
#include "../../resource/texture/cubeMapTexture.h"

class Skybox
{
public:

    // Rotation speed of the skybox
    static const float ROTATE_SPEED;

    // Constructor
    Skybox();

    // Destructor
    ~Skybox();

    // Get the rotation angle
    float getAngle() const;

    // Get the cube model
    RawModel* getModel() const;

    // Get the cube map texture
    CubeMapTexture* getTexture() const;

    // Rotate skybox
    void rotate();

private:

    // Raw cube model
    RawModel* model;

    // Cube map texture
    CubeMapTexture* texture;

    // Rotation angle of the skybox
    float angle;
};

#endif
