#include "staticShader.h"

// Vertex shader file name
const char* StaticShader::VERTEX_FILE = "src/render/shaders/shaderSource/staticVertexShader.glsl";

// Fragment shader file name
const char* StaticShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/staticFragmentShader.glsl";

// Constructor
StaticShader::StaticShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE, SHADER_LOAD_LIGHT | SHADER_LOAD_CLIP | SHADER_BIND_TEX_NORM)
{
    getAllUniformLocs();
}

// Load texture property into shader program
void StaticShader::loadTexture(float reflectivity, float shineDamper)
{
    loadFloat(reflectivityLoc, reflectivity);
    loadFloat(shineDamperLoc, shineDamper);
}

// Get all uniform locations
void StaticShader::getAllUniformLocs()
{
    reflectivityLoc = getUniformLoc("reflectivity");
    shineDamperLoc = getUniformLoc("shineDamper");
}
