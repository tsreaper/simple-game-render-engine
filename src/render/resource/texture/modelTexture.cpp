#include "modelTexture.h"

// Constructor
ModelTexture::ModelTexture(
    const char* _name, GLuint id, float _reflectivity, float _shineDamper, bool _transparency
): name(_name), textureId(id), reflectivity(_reflectivity), shineDamper(_shineDamper), transparency(_transparency) {}

// Destructor
ModelTexture::~ModelTexture()
{
    glDeleteTextures(1, &textureId);
}

// Get texture name
const char* ModelTexture::getName() const
{
    return name.c_str();
}

// Get texture id
GLuint ModelTexture::getId() const
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

// Get transparency
bool ModelTexture::getTransparency() const
{
    return transparency;
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

// Set transparency
void ModelTexture::setTransparency(float _transparency)
{
    transparency = _transparency;
}
