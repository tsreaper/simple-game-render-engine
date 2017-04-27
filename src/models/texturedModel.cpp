#include "texturedModel.h"

TexturedModel::TexturedModel(RawModel* _raw, ModelTexture* _texture)
{
    raw = _raw;
    texture = _texture;
}

RawModel* TexturedModel::getRaw()
{
    return raw;
}

ModelTexture* TexturedModel::getTexture()
{
    return texture;
}
