#ifndef _TERRAIN_RENDERER_H
#define _TERRAIN_RENDERER_H

#include "glew.h"
#include "render/object/light/light.h"
#include "render/object/terrain/terrain.h"
#include "render/object/terrain/terrainShader.h"

// Terrain renderer
class TerrainRenderer
{
public:

    // Render a terrain
    void render(const Terrain* terrain, Light* light[], int lightSize, TerrainShader* shader);

    // Bind a terrain
    void bindTerrain(const Terrain* terrain);

    // Unbind a terrain
    void unbindTerrain();

private:

    // Sort light
    void sortLight(Light* light[], int lightSize);
};

#endif
