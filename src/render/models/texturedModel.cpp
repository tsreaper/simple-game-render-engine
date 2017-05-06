#include "../engine/memoryManager.h"
#include "texturedModel.h"

// Constructor
TexturedModel::TexturedModel(const char* _name, RawModel* _raw, ModelTexture* _texture)
{
    name = _name;
    raw = _raw;
    texture = _texture;
}

// Destructor
TexturedModel::~TexturedModel()
{
    MemoryManager::deleteRawModel(raw);
    MemoryManager::deleteModelTexture(texture);
}

// Get model name
const char* TexturedModel::getName() const
{
    return name.c_str();
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
