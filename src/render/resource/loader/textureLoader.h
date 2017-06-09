#ifndef _TEXTURE_LOADER
#define _TEXTURE_LOADER

#include "render/resource/texture/plainTexture.h"
#include "render/resource/texture/modelTexture.h"
#include "render/resource/texture/terrainTexture.h"
#include "render/resource/texture/cubeMapTexture.h"

class TextureLoader
{
public:

    // Create plain texture
    static PlainTexture* loadPlainTexture(const char* name);

    // Create model texture
    static ModelTexture* loadModelTexture(const char* name);

    // Create terrain texture
    static TerrainTexture* loadTerrainTexture(const char* name);

    // Create cube map texture
    static CubeMapTexture* loadCubeMapTexture(const char* name);

private:

    // Create texture from file
    static GLuint loadTexture(const char* filename);
};

#endif
