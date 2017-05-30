#include "plainTexture.h"

// Constructor
PlainTexture::PlainTexture(const char* _name, GLuint id): name(_name), textureId(id) {}

// Destructor
PlainTexture::~PlainTexture()
{
    glDeleteTextures(1, &textureId);
}

// Get texture name
const char* PlainTexture::getName() const
{
    return name.c_str();
}

// Get texture id
GLuint PlainTexture::getId() const
{
    return textureId;
}
