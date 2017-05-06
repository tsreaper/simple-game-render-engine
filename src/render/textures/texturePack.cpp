#include "../engine/memoryManager.h"
#include "texturePack.h"

// Constructor
TexturePack::TexturePack(const char* _name, ModelTexture* _k, ModelTexture* _r, ModelTexture* _g, ModelTexture* _b, ModelTexture* _blend)
{
    name = _name;
    k = _k; r = _r; g = _g; b = _b;
    blend = _blend;
}

// Destructor
TexturePack::~TexturePack()
{
    MemoryManager::deleteModelTexture(k);
    MemoryManager::deleteModelTexture(r);
    MemoryManager::deleteModelTexture(g);
    MemoryManager::deleteModelTexture(b);
    MemoryManager::deleteModelTexture(blend);
}

// Get name of texture pack
const char* TexturePack::getName() const
{
    return name.c_str();
}

// Get black texture
ModelTexture* TexturePack::getK() const
{
    return k;
}

// Get red texture
ModelTexture* TexturePack::getR() const
{
    return r;
}

// Get green texture
ModelTexture* TexturePack::getG() const
{
    return g;
}

// Get blue texture
ModelTexture* TexturePack::getB() const
{
    return b;
}

// Get blend map
ModelTexture* TexturePack::getBlend() const
{
    return blend;
}
