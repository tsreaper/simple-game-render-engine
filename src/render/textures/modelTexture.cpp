#include "modelTexture.h"

// Constructor
ModelTexture::ModelTexture(int id)
{
    textureId = id;
}

// Get texture id
int ModelTexture::getId() const
{
    return textureId;
}
