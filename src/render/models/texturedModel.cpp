#include "texturedModel.h"

// Constructor
TexturedModel::TexturedModel(RawModel* _raw, ModelTexture* _texture)
{
    raw = _raw;
    texture = _texture;
}

// Get raw model pointer
RawModel* TexturedModel::getRaw() const
{
    return raw;
}

// Get texture pointer
ModelTexture* TexturedModel::getTexture() const
{
    return texture;
}
