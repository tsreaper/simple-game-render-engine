#include "render/resource/manager/resourceManager.h"
#include "render/resource/model/geometricModel.h"
#include "render/object/skybox/skybox.h"

// Rotation speed of the skybox
const float Skybox::ROTATE_SPEED = 0.0003;

// Constructor
Skybox::Skybox(const char* dayTextureName, const char* nightTextureName)
{
    model = GeometricModel::getGeometricModel(GeometricModel::CUBE);
    dayTexture = ResourceManager::getResource<CubeMapTexture>(dayTextureName);
    nightTexture = ResourceManager::getResource<CubeMapTexture>(nightTextureName);
    angle = 0;
}

// Destructor
Skybox::~Skybox()
{
    ResourceManager::deleteResource<CubeMapTexture>(dayTexture);
    ResourceManager::deleteResource<CubeMapTexture>(nightTexture);
}

// Get the rotation angle
float Skybox::getAngle() const
{
    return angle;
}

// Get night factor
float Skybox::getNightFac() const
{
    return nightFac;
}

// Get the cube model
RawModel* Skybox::getModel() const
{
    return model;
}

// Get the cube map texture
CubeMapTexture* Skybox::getDayTexture() const
{
    return dayTexture;
}
CubeMapTexture* Skybox::getNightTexture() const
{
    return nightTexture;
}

// Set night factor
void Skybox::setNightFac(float _fac)
{
    nightFac = _fac;
}

// Rotate skybox
void Skybox::rotate()
{
    angle += ROTATE_SPEED;
}
