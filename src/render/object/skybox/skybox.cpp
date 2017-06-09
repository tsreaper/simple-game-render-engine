#include "render/resource/manager/resourceManager.h"
#include "render/resource/model/geometricModel.h"
#include "render/object/skybox/skybox.h"

// Rotation speed of the skybox
const float Skybox::ROTATE_SPEED = 0.0001;

// Constructor
Skybox::Skybox()
{
    model = GeometricModel::getGeometricModel(GeometricModel::CUBE);
    texture = ResourceManager::getResource<CubeMapTexture>("skybox");
    angle = 0;
}

// Destructor
Skybox::~Skybox()
{
    ResourceManager::deleteResource<CubeMapTexture>(texture);
}

// Get the rotation angle
float Skybox::getAngle() const
{
    return angle;
}

// Get the cube model
RawModel* Skybox::getModel() const
{
    return model;
}

// Get the cube map texture
CubeMapTexture* Skybox::getTexture() const
{
    return texture;
}

// Rotate skybox
void Skybox::rotate()
{
    angle += ROTATE_SPEED;
}
