#ifndef TERRAIN_RENDERER_H_
#define TERRAIN_RENDERER_H_

#include "../../glew.h"
#include "../terrains/terrain.h"
#include "../shaders/terrainShader.h"

// Terrain renderer
class TerrainRenderer
{
public:
    
    // Render a terrain
    static void render(const Terrain* terrain, TerrainShader* shader);
    
    // Bind a terrain
    static void bindTerrain(const Terrain* terrain, TerrainShader* shader);
    
    // Unbind a terrain
    static void unbindTerrain();
};

#endif
