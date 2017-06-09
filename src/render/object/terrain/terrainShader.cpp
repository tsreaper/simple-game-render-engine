#include "render/object/terrain/terrainShader.h"

// Vertex shader file name
const char* TerrainShader::VERTEX_FILE = "src/render/object/terrain/terrainVertex.glsl";

// Fragment shader file name
const char* TerrainShader::FRAGMENT_FILE = "src/render/object/terrain/terrainFragment.glsl";

// Constructor
TerrainShader::TerrainShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE, SHADER_LOAD_LIGHT | SHADER_LOAD_CLIP | SHADER_BIND_TEX_NORM)
{
    getAllUniformLocs();

    start();
    connectTextures();
    stop();
}

// Get all uniform locations
void TerrainShader::getAllUniformLocs()
{
    kLoc = getUniformLoc("textureK");
    rLoc = getUniformLoc("textureR");
    gLoc = getUniformLoc("textureG");
    bLoc = getUniformLoc("textureB");
    blendLoc = getUniformLoc("blendMap");
}

// Connect texture units to shader program
void TerrainShader::connectTextures()
{
    loadInt(kLoc, 0);
    loadInt(rLoc, 1);
    loadInt(gLoc, 2);
    loadInt(bLoc, 3);
    loadInt(blendLoc, 4);
}
