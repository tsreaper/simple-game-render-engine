#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "render/resource/model/rawModel.h"
#include "render/resource/texture/cubeMapTexture.h"

class Skybox
{
public:

    // Rotation speed of the skybox
    static const float ROTATE_SPEED;

    // Constructor
    Skybox(const char* dayTextureName, const char* nightTextureName);

    // Destructor
    ~Skybox();

    // Get rotation angle
    float getAngle() const;

    // Get night factor
    float getNightFac() const;

    // Get the cube model
    RawModel* getModel() const;

    // Get the cube map texture
    CubeMapTexture* getDayTexture() const;
    CubeMapTexture* getNightTexture() const;

    // Set night factor
    void setNightFac(float _fac);

    // Rotate skybox
    void rotate();

private:

    // Rotation angle of the skybox
    float angle;

    // Night factor
    float nightFac;

    // Raw cube model
    RawModel* model;

    // Cube map texture
    CubeMapTexture* dayTexture;
    CubeMapTexture* nightTexture;
};

#endif
