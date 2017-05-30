#ifndef _TERRAIN_RENDERER_H
#define _TERRAIN_RENDERER_H

#include "../../../glew.h"
#include "terrain.h"
#include "terrainShader.h"

// Terrain renderer
class TerrainRenderer
{
public:

    // Render a terrain
    void render(const Terrain* terrain, TerrainShader* shader);

    // Bind a terrain
    void bindTerrain(const Terrain* terrain);

    // Unbind a terrain
    void unbindTerrain();
};

#endif
