#include "terrainShader.h"

// Vertex shader file name
const char* TerrainShader::VERTEX_FILE = "src/render/shaders/shaderSource/terrainVertexShader.glsl";

// Fragment shader file name
const char* TerrainShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/terrainFragmentShader.glsl";

// Constructor
TerrainShader::TerrainShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE)
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
