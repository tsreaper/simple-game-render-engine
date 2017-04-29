#include "modelTexture.h"

// Constructor
ModelTexture::ModelTexture(int id, float _reflectivity, float _shineDamper)
{
    textureId = id;
    reflectivity = _reflectivity;
    shineDamper = _shineDamper;
}

// Get texture id
int ModelTexture::getId() const
{
    return textureId;
}

// Get reflectivity
float ModelTexture::getReflectivity() const
{
    return reflectivity;
}

// Get shine damper
float ModelTexture::getShineDamper() const
{
    return shineDamper;
}

// Set reflectivity
void ModelTexture::setReflectivity(float _reflectivity)
{
    reflectivity = _reflectivity;
}

// Set shine damper
void ModelTexture::setShineDamper(float _shineDamper)
{
    shineDamper = _shineDamper;
}
