#include "render/object/entity/entityShader.h"

// Vertex shader file name
const char* EntityShader::VERTEX_FILE = "src/render/object/entity/entityVertex.glsl";

// Fragment shader file name
const char* EntityShader::FRAGMENT_FILE = "src/render/object/entity/entityFragment.glsl";

// Constructor
EntityShader::EntityShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE, SHADER_LOAD_LIGHT | SHADER_LOAD_CLIP | SHADER_BIND_TEX_NORM)
{
    getAllUniformLocs();
}

// Load texture property into shader program
void EntityShader::loadTexture(float reflectivity, float shineDamper, int atlasRows)
{
    loadFloat(reflectivityLoc, reflectivity);
    loadFloat(shineDamperLoc, shineDamper);
    loadInt(atlasRowsLoc, atlasRows);
}

// Load atlas position into shader program
void EntityShader::loadAtlasPos(int atlasPos)
{
    loadInt(atlasPosLoc, atlasPos);
}

// Get all uniform locations
void EntityShader::getAllUniformLocs()
{
    reflectivityLoc = getUniformLoc("reflectivity");
    shineDamperLoc = getUniformLoc("shineDamper");
    atlasRowsLoc = getUniformLoc("atlasRows");
    atlasPosLoc = getUniformLoc("atlasPos");
}
