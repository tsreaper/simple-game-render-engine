#include "render/resource/texture/cubeMapTexture.h"

// Constructor
CubeMapTexture::CubeMapTexture(
    const char* _name, GLuint id
): name(_name), textureId(id) {}

// Destructor
CubeMapTexture::~CubeMapTexture()
{
    glDeleteTextures(1, &textureId);
}

// Get texture name
const char* CubeMapTexture::getName() const
{
    return name.c_str();
}

// Get texture id
GLuint CubeMapTexture::getId() const
{
    return textureId;
}
