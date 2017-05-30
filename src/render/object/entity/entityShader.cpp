#include "entityShader.h"

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
void EntityShader::loadTexture(float reflectivity, float shineDamper)
{
    loadFloat(reflectivityLoc, reflectivity);
    loadFloat(shineDamperLoc, shineDamper);
}

// Get all uniform locations
void EntityShader::getAllUniformLocs()
{
    reflectivityLoc = getUniformLoc("reflectivity");
    shineDamperLoc = getUniformLoc("shineDamper");
}
